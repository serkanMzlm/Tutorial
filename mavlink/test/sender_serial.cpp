#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <mavlink/common/mavlink.h>
#include <csignal> 
#include <chrono>
#include <thread>

// Global değişken: Sinyal durumunu tutacak değişken
volatile sig_atomic_t exit_flag = 0;

// Seri port ayarları
int set_serial_attribs(int fd, int speed) {
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr failed");
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit characters
    tty.c_iflag &= ~IGNBRK;                        // disable break processing
    tty.c_lflag = 0;                               // no signaling chars, no echo,
                                                   // no canonical processing
    tty.c_oflag = 0;                               // no remapping, no delays
    tty.c_cc[VMIN]  = 0;                            // read doesn't block
    tty.c_cc[VTIME] = 5;                            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);        // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);               // ignore modem controls,
                                                   // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);             // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr failed");
        return -1;
    }
    return 0;
}

// Sinyal işleyici fonksiyonu
void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Ctrl+C detected, exiting..." << std::endl;
        exit_flag = 1;
    }
}

// Heartbeat mesajı gönderme fonksiyonu
void sendHeartbeat(int fd) {
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len;

    uint8_t system_id = 12;
    uint8_t component_id = 65;
    uint8_t type = MAV_TYPE_QUADROTOR;
    uint8_t autopilot = MAV_AUTOPILOT_GENERIC;
    uint8_t base_mode = MAV_MODE_MANUAL_ARMED;
    uint32_t custom_mode = 0;
    uint8_t system_status = MAV_STATE_ACTIVE;

    mavlink_msg_heartbeat_pack(system_id, component_id, &msg, type, autopilot, base_mode, custom_mode, system_status);

    len = mavlink_msg_to_send_buffer(buf, &msg);

    ssize_t bytes_sent = write(fd, buf, len);
    if (bytes_sent == -1) {
        perror("write failed");
    } else {
        std::cout << "Heartbeat message sent (" << bytes_sent << " bytes)" << std::endl;
    }
}

// MAVLink mesajlarını okuma ve işleme fonksiyonu
void receiveMavlinkMessage(int fd) {
    mavlink_message_t msg;
    mavlink_status_t status;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    // Veri al
    ssize_t bytes_received = read(fd, buf, sizeof(buf));
    if (bytes_received == -1) {
        perror("read failed");
        return;
    }

    // Alınan veriyi çözümle
    for (ssize_t i = 0; i < bytes_received; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
            // Ekrana mesaj türünü ve bilgilerini yaz
            std::cout << "Received MAVLink Message ID: " << static_cast<int>(msg.msgid) << std::endl;
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                // MAVLink HEARTBEAT mesajını işle
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                std::cout << "Heartbeat Status: " << static_cast<int>(heartbeat.system_status) << std::endl;
            }
        }
    }
}

int main() {
    const char *serial_port = "/dev/ttyACM1"; // Seri port adı (Linux)
    const int serial_speed = B57600;         // Seri port hızı

    // Seri portu aç
    int fd = open(serial_port, O_RDWR | O_NOCTTY | O_SYNC);
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
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);

    // Ana döngü
    while (!exit_flag) {
        sendHeartbeat(fd);
        receiveMavlinkMessage(fd);
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 saniye bekleme (1 Hz)
    }

    // Seri portu kapat
    close(fd);
    return 0;
}
