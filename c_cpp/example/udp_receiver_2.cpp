
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to Create Socket" << std::endl;
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4557); 
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection Failed!" << std::endl;
        close(sockfd);
        return -1;
    }
    std::cout << "Port is Listening..." << std::endl;
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);

        ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (len < 0) {
            std::cerr << "Message Reception Failed!" << std::endl;
            break;
        }
        std::cout << "IP: " << inet_ntoa(client_addr.sin_addr) <<
            " Message: " << buffer << std::endl;
    }

    close(sockfd);
    return 0;
}