#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <mavlink/common/mavlink.h>

// UDP soketini açma ve ayarlama fonksiyonu
int open_udp_socket(int port) {
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

void receive_heartbeat(int sockfd) {
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
    const int local_port = 14550; // Yerel port

    // UDP soketini aç
    int sockfd = open_udp_socket(local_port);
    if (sockfd == -1) {
        return 1;
    }

    // Mesaj alma döngüsü (2 Hz)
    while (true) {
        receive_mavlink_message(sockfd);
        usleep(500000); // 500,000 mikrosaniye = 0.5 saniye bekleme (2 Hz)
    }

    // Soketi kapat
    close(sockfd);
    return 0;
}
