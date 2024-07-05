#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "mavlink/common/mavlink.h"

#define SERIAL_PORT "/dev/ttyACM1"  // Seri port adı

int main() {
    int system_id = 1;  // Sistem kimliği (örneğin, 1: GCS)
    int component_id = 1;  // Bileşen kimliği (örneğin, 1: MAV_AUTOPILOT_GENERIC)

    // Seri bağlantıyı aç
    int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        std::cerr << "Seri port açılamadı." << std::endl;
        return -1;
    }

    // Seri port ayarlarını yapılandır
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

    // 1'den 100'e kadar olan sayıları MAVLink mesajları olarak gönder
    for (int sayi = 1; sayi <= 100; sayi++) {
        mavlink_message_t msg;
        mavlink_heartbeat_t heartbeat;
        heartbeat.type = MAV_TYPE_GCS;
        heartbeat.autopilot = MAV_AUTOPILOT_GENERIC;
        heartbeat.base_mode = 0;
        heartbeat.custom_mode = sayi;  // Sayıyı custom_mode alanına yerleştir
        heartbeat.system_status = MAV_STATE_ACTIVE;
        mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &heartbeat);

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        int len = mavlink_msg_to_send_buffer(buffer, &msg);

        if (write(fd, buffer, len) < 0) {
            std::cerr << "Mesaj gönderme hatası." << std::endl;
            close(fd);
            return -1;
        }

        std::cout << "tx: " << sayi << std::endl;
        sleep(1);  // 1 saniye bekle
    }

    close(fd);
    return 0;
}
