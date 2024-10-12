#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Soket oluştur
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed." << std::endl;
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Server adresini ayarla
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(4557);  // Port numarası
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Soketi porta bağla
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed." << std::endl;
        close(sockfd);
        return -1;
    }

    uint8_t buffer[1024];  // uint8_t veri alacak buffer
    socklen_t len = sizeof(cliaddr);

    std::cout << "Listening on port 4557..." << std::endl;

    // Sürekli dinleme döngüsü
    while (true) {
        // Mesaj al
        int n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL,
                         (struct sockaddr *) &cliaddr, &len);
        if (n > 0) {
            std::cout << "Received message: ";
            // for (int i = 0; i < n; ++i) {
            //     std::cout << static_cast<int>(buffer[i]) << " ";  // uint8_t değerlerini ekrana yaz
            // }
            std::cout << buffer << std::endl;
        } else {
            std::cerr << "Failed to receive message." << std::endl;
        }
    }

    close(sockfd);
    return 0;
}
