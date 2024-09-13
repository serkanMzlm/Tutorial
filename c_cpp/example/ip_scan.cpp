#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    struct sockaddr_in serv;
    std::memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(80);
    inet_pton(AF_INET, "8.8.8.8", &serv.sin_addr);

    int err = connect(sock, (const struct sockaddr *)&serv, sizeof(serv));
    if (err < 0)
    {
        std::cerr << "Connection failed.\n";
        close(sock);
        return 1;
    }

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr *)&name, &namelen);
    if (err < 0)
    {
        std::cerr << "getsockname() failed.\n";
        close(sock);
        return 1;
    }

    char buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &name.sin_addr, buffer, sizeof(buffer));
    std::cout << "Active local IP address: " << buffer << std::endl;

    close(sock);
    return 0;
}
