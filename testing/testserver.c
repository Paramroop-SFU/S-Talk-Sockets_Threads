#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

int main() {
    char buffer[50] = {0};
    const char* hostname = "asb9700u-g02";
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int hostIP = getaddrinfo(hostname, "12345", &hints, &res);
    if (hostIP != 0) {
        perror("getaddrinfo() failed");
        return -1;
    }

    int dest = socket(AF_INET, SOCK_DGRAM, 0);
    if (dest == -1) {
        perror("socket() failed");
        return -1;
    }

    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    freeaddrinfo(res);  // Free the linked list

    int rc = bind(dest, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    if (rc == -1) {
        perror("bind() failed");
        close(dest);
        return -1;
    }

    socklen_t len = sizeof(servaddr);
    while (1) {
        int n = recvfrom(dest, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&servaddr, &len);
        if (n == -1) {
            perror("recvfrom() failed");
            break;
        }

        buffer[n] = '\0';  // Null-terminate the received data
        printf("%s\n", buffer);
        sleep(12);
    }

    close(dest);
    return 0;
}
