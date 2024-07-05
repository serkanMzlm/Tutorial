#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include "mavlink/common/mavlink.h"

#define TARGET_IP "127.0.0.1"  // Hedef IP adresi
#define TARGET_PORT 14550     // Hedef Port numarası

int main() {
    int system_id = 1;  // Sistem kimliği (örneğin, 1: GCS)
    int component_id = 1;  // Bileşen kimliği (örneğin, 1: MAV_AUTOPILOT_GENERIC)

    int udp_port = 14555;  // Kendi UDP port numarası

    // UDP bağlantısı oluşturunuz
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket oluşturulamadı." << std::endl;
        return -1;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(udp_port);
    sockaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cerr << "Bind işlemi başarısız." << std::endl;
        close(sockfd);
        return -1;
    }

    struct sockaddr_in destaddr;
    destaddr.sin_family = AF_INET;
    destaddr.sin_port = htons(TARGET_PORT);
    if (inet_pton(AF_INET, TARGET_IP, &destaddr.sin_addr) <= 0) {
        std::cerr << "Geçersiz IP adresi." << std::endl;
        close(sockfd);
        return -1;
    }

    // 1'den 100'e kadar olan sayıları MAVLink mesajları olarak gönderin
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

        if (sendto(sockfd, buffer, len, 0, (struct sockaddr *)&destaddr, sizeof(destaddr)) < 0) {
            std::cerr << "Mesaj gönderme hatası." << std::endl;
            close(sockfd);
            return -1;
        }

        std::cout << "tx: " << sayi << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }

    close(sockfd);

    return 0;
}
