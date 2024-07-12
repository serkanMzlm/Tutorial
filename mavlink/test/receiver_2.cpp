#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <mavlink/common/mavlink.h>

// Heartbeat mesajı alma ve işleme fonksiyonu
void receive_heartbeat(int sockfd) {
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    // UDP soketi üzerinden mesaj al
    ssize_t bytes_received = recvfrom(sockfd, buf, MAVLINK_MAX_PACKET_LEN, 0, (struct sockaddr *)&src_addr, &addr_len);
    if (bytes_received == -1) {
        perror("recvfrom failed");
        return;
    }

    // Mesajı çözümle
    mavlink_message_t msg;
    mavlink_status_t status;

    for (ssize_t i = 0; i < bytes_received; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                std::cout << "Heartbeat received: System ID=" << static_cast<int>(msg.sysid)
                          << ", Component ID=" << static_cast<int>(msg.compid)
                          << std::endl;
            }
        }
    }   
}

int main() {
    const int local_port = 14551; // Yerel port
    const char *remote_ip = "127.0.0.1"; // Uzak IP adresi
    const int remote_port = 14550; // Uzak port

    // UDP soketi oluşturma
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        return 1;
    }

    sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(local_port);

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
        perror("bind failed");
        close(sockfd);
        return 1;
    }

    sockaddr_in remote_addr;
    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);
    if (inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr) != 1) {
        perror("inet_pton failed");
        close(sockfd);
        return 1;
    }

    while (true) {
        receive_heartbeat(sockfd);
    }

    close(sockfd);
    return 0;
}
