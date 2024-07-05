#include <cstring>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <csignal> 

#include <fcntl.h>
#include <termios.h>

#include <chrono>
#include <thread>
#include <csignal> 

#include <mavlink/common/mavlink.h>

#define MAV_CHANNEL MAVLINK_COMM_0
#define LOCAL_PORT 14550

volatile sig_atomic_t exit_flag = 0;
bool flag = true;

void receiveHeartbeatUdp(int sockfd);
int openUdpSocket(int port);

void receiveHeartbeatSerial(int fd);
int setSerialAttribs(int fd, int speed);

void signalHandler(int signum);

int main(int argc, char** argv)
{
    const char *serial_port = "/dev/ttyACM0"; 
    const int serial_speed = B57600;  
    int sockfd;
    int fd; 

    if(flag)
    {
        sockfd = openUdpSocket(LOCAL_PORT);
        if (sockfd == -1) {
            return 1;
        }
    }
    else 
    {
        fd = open(serial_port, O_RDWR | O_NOCTTY | O_SYNC);
        if (fd == -1) {
            perror("open_serial failed");
            return 1;
        }

        if (setSerialAttribs(fd, serial_speed) == -1) {
            return 1;
        }
    }

    struct sigaction sig;
    sig.sa_handler = signalHandler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, nullptr);
    
    while (!exit_flag) {
        if(flag)
        {
            receiveHeartbeatUdp(sockfd);
        }
        else
        {
            receiveHeartbeatSerial(fd);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    if(flag)
    {
        close(sockfd);
    }
    else
    {
        close(fd);
    }
    return 0;
}

void receiveHeartbeatUdp(int sockfd)
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    ssize_t bytes_received = recvfrom(sockfd, buf, MAVLINK_MAX_PACKET_LEN, 0, (struct sockaddr *)&src_addr, &addr_len);

    if (bytes_received == -1) {
        perror("recvfrom failed");
        return;
    }

    mavlink_message_t msg;
    mavlink_status_t status;

    for (ssize_t i = 0; i < bytes_received; ++i) {
        if (mavlink_parse_char(MAV_CHANNEL, buf[i], &msg, &status)) {
            std::cout << "System ID=" << static_cast<int>(msg.sysid)
                        << ", Component ID=" << static_cast<int>(msg.compid) 
                        << ", MAVLink Message ID: " << static_cast<int>(msg.msgid) 
                          << std::endl;
        }
    } 
}

int openUdpSocket(int port)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        return -1;
    }

    sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("bind failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Ctrl+C detected, exiting..." << std::endl;
        exit_flag = 1;
    }
}

void receiveHeartbeatSerial(int fd)
{
    mavlink_message_t msg;
    mavlink_status_t status;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    ssize_t bytes_received = read(fd, buf, sizeof(buf));
    if (bytes_received == -1) {
        perror("read failed");
        return;
    }

    for (ssize_t i = 0; i < bytes_received; ++i) {
        if (mavlink_parse_char(MAV_CHANNEL, buf[i], &msg, &status)) {
            std::cout << "System ID=" << static_cast<int>(msg.sysid)
                        << ", Component ID=" << static_cast<int>(msg.compid) 
                        << ", MAVLink Message ID: " << static_cast<int>(msg.msgid) 
                          << std::endl;
        }
    } 
}

int setSerialAttribs(int fd, int speed)
{
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
