#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <mavlink/common/mavlink.h>

// Heartbeat mesajı gönderme fonksiyonu
void send_heartbeat(int sockfd, const sockaddr_in &dest_addr) {
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len;

    // Heartbeat mesajı parametreleri
    uint8_t system_id = 12;
    uint8_t component_id = 65;
    uint8_t type = MAV_TYPE_QUADROTOR;
    uint8_t autopilot = MAV_AUTOPILOT_GENERIC;
    uint8_t base_mode = MAV_MODE_MANUAL_ARMED;
    uint32_t custom_mode = 0;
    uint8_t system_status = MAV_STATE_ACTIVE;

    // Heartbeat mesajını doldur
    mavlink_msg_heartbeat_pack(system_id, component_id, &msg, type, autopilot, base_mode, custom_mode, system_status);

    // Mesajı seri bağlantı için paketle
    len = mavlink_msg_to_send_buffer(buf, &msg);

    // Mesajı UDP soketi üzerinden gönder
    ssize_t bytes_sent = sendto(sockfd, buf, len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent == -1) {
        perror("sendto failed");
    } else {
        std::cout << "Heartbeat message sent (" << bytes_sent << " bytes)" << std::endl;
    }
}

int main() {
    const int local_port = 14550; // Yerel port
    const char *remote_ip = "127.0.0.1"; // Uzak IP adresi
    const int remote_port = 14551; // Uzak port

    // UDP soketi oluşturma
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        return 1;
    }

    // Yerel adres ve bağlantı noktasını ayarlama
    sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(local_port);

    // Soketi yerel adrese bağlama
    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
        perror("bind failed");
        close(sockfd);
        return 1;
    }

    // Uzak adres ve bağlantı noktasını ayarlama
    sockaddr_in remote_addr;
    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);
    if (inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr) != 1) {
        perror("inet_pton failed");
        close(sockfd);
        return 1;
    }

    // Mesaj gönderme döngüsü
    while (true) {
        send_heartbeat(sockfd, remote_addr);
        sleep(1); // 1 saniye bekleme
    }

    // Soketi kapatma
    close(sockfd);
    return 0;
}
