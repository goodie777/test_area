#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    struct sockaddr_in serverInfo = {0};
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(5555);
    serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return -1;
    }

    // connect
    if (connect(fd, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == -1) {
        perror("connect");
        close(fd);
        return -1;
    }

    printf("Connected to server!\n");

    char *msg = "Hello from client!";
    send(fd, msg, 18, 0);

    close(fd);
    return 0;
}