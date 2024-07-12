#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <chrono>
#include <thread>
#include <csignal> 

#include <mavlink/common/mavlink.h>

volatile sig_atomic_t exit_flag = 0;
int fd;

int set_serial_attribs(int fd, int speed) {
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr failed");
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;   
    tty.c_iflag &= ~IGNBRK;                       
    tty.c_lflag = 0;                              
                                                  
    tty.c_oflag = 0;                              
    tty.c_cc[VMIN]  = 0;                          
    tty.c_cc[VTIME] = 5;                          

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);       

    tty.c_cflag |= (CLOCAL | CREAD);              
                                                  
    tty.c_cflag &= ~(PARENB | PARODD);            
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr failed");
        return -1;
    }
    return 0;
}

void receive_mavlink_message(int fd) {
    mavlink_message_t msg;
    mavlink_status_t status;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    ssize_t bytes_received = read(fd, buf, sizeof(buf));
    if (bytes_received == -1) {
        perror("read failed");
        return;
    }

    for (ssize_t i = 0; i < bytes_received; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
            std::cout << "Received MAVLink Message ID: " << static_cast<int>(msg.msgid) << std::endl;
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                std::cout << "Heartbeat Status: " << static_cast<int>(heartbeat.system_status) << std::endl;
            }
        }
    }
}

void signal_handler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Ctrl+C detected, exiting..." << std::endl;
        close(fd);
        exit_flag = 1;
    }
}

int main() {
    const char *serial_port = "/dev/ttyACM1"; 
    const int serial_speed = B57600;         

    // Seri portu aç
   fd = open(serial_port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd == -1) {
        perror("open_serial failed");
        return 1;
    }

    // Seri port ayarlarını yap
    if (set_serial_attribs(fd, serial_speed) == -1) {
        return 1;
    }

    // Sinyal işleyiciyi tanımla
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);

    // Ana döngü
    while (!exit_flag) {
        receive_mavlink_message(fd);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }

    // Seri portu kapat
    close(fd);
    return 0;
}
