#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <thread>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    const char* server_ip = "192.168.20.103";  
    int server_port = 4557;  

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to Create Socket!" << std::endl;
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid Address or Address not Supported!" << std::endl;
        close(sockfd);
        return -1;
    }

    const int count = 20;
    int numbers[count];
    for (int i = 0; i < count; ++i) {
        numbers[i] = 32;
    }

    for (int i = 1; i <= 100; ++i) {
        int a = 10;
         ssize_t sent_bytes = sendto(sockfd, &numbers, sizeof(numbers), 0, 
                                    (struct sockaddr*)&server_addr, sizeof(server_addr));


        if (sent_bytes < 0) {
            std::cerr << "Message Sending Failed!" << std::endl;
            break;
        }

        std::cout << "Message Sent: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    close(sockfd);
    return 0;
}