#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // Soket oluşturma
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Soket oluşturulamadı.\n";
        return 1;
    }

    // Yayın izni ver
    int broadcastEnable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) < 0) {
        std::cerr << "Yayın izni verilemedi.\n";
        close(sock);
        return 1;
    }

    // Yayın adresini ayarla
    struct sockaddr_in broadcastAddr;
    std::memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_port = htons(5000);  // Test için rastgele port
    inet_pton(AF_INET, "255.255.255.255", &broadcastAddr.sin_addr);

    // Yayın paketini gönder
    const char *message = "Merhaba, Yayın!";
    if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0) {
        std::cerr << "Yayın paketi gönderilemedi.\n";
        close(sock);
        return 1;
    }

    // Yanıt dinle
    struct sockaddr_in recvAddr;
    socklen_t addrLen = sizeof(recvAddr);
    char buffer[1024];

    std::cout << "Yanıtlar dinleniyor..." << std::endl;

    // Yanıt almak için zaman aşımı ayarla (isteğe bağlı)
    struct timeval tv;
    tv.tv_sec = 5;  // 5 saniyelik zaman aşımı
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    int recvLen = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&recvAddr, &addrLen);
    if (recvLen > 0) {
        buffer[recvLen] = '\0';
        char addrBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &recvAddr.sin_addr, addrBuffer, sizeof(addrBuffer));
        std::cout << "Yanıt şuradan alındı: " << addrBuffer << " - Mesaj: " << buffer << std::endl;
    } else {
        std::cout << "Zaman aşımı süresi içinde yanıt alınamadı." << std::endl;
    }

    // Soketi kapat
    close(sock);
    return 0;
}
