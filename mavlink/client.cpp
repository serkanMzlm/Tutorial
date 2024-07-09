#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "mavlink/common/mavlink.h"

#define MY_IP "127.0.0.1" 
#define MY_PORT 14550     

int main() {
    int udp_port = 14550; 

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

    while (true) {
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        ssize_t recsize = recv(sockfd, (void *)buffer, MAVLINK_MAX_PACKET_LEN, 0);

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
                            close(sockfd);  
                            return 0; 
                        }
                    }
                }
            }
        } else if (recsize < 0) {
            std::cerr << "Mesaj alma hatası." << std::endl;
            close(sockfd);
            return -1;
        }
    }

    close(sockfd);
    return 0;
}
