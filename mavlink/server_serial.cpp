#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "mavlink/common/mavlink.h"

#define SERIAL_PORT "/dev/ttyACM1" 

int main() {
    int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        std::cerr << "Seri port açılamadı." << std::endl;
        return -1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Seri port ayarları okunamadı." << std::endl;
        close(fd);
        return -1;
    }
    cfsetospeed(&tty, B57600);
    cfsetispeed(&tty, B57600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &tty);

    while (true) {
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        ssize_t recsize = read(fd, buffer, sizeof(buffer));

        if (recsize > 0) {
            mavlink_message_t msg;
            mavlink_status_t status;
            for (ssize_t i = 0; i < recsize; i++) {
                if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
                    if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                        mavlink_heartbeat_t heartbeat;
                        mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                        std::cout << "rx: " << heartbeat.custom_mode << std::endl;

                        if (heartbeat.custom_mode == 99) {
                            close(fd); 
                            return 0; 
                        }
                    }
                }
            }
        } else if (recsize < 0) {
            std::cerr << "Mesaj alma hatası." << std::endl;
            close(fd);
            return -1;
        }
    }

    close(fd);
    return 0;
}
