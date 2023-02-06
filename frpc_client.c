#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Failed to create socket: %s\n", strerror(errno));
        exit(1);
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        printf("Failed to set socket options: %s\n", strerror(errno));
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7000);

    // if (inet_pton(AF_INET, "ambicamp2p.vmukti.com", &serv_addr.sin_addr) <= 0)
    // {
    //     printf("Invalid address: %s\n", strerror(errno));
    //     exit(1);
    // }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Failed to connect: %s\n", strerror(errno));
        exit(1);
    }

    char buffer[1024];
    memset(buffer, 0, 1024);
    sprintf(buffer, "Hello from frpc client\n");

    if (send(sock, buffer, strlen(buffer), 0) < 0)
    {
        printf("Failed to send data: %s\n", strerror(errno));
        exit(1);
    }

    printf("Data sent successfully\n");
    close(sock);
    return 0;
}
