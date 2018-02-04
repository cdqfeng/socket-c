#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNUM 6789

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    struct hostent *host;
    int nbytes;

    host = gethostbyname(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUM);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    int ret = connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
    while ((nbytes = read(sockfd, buffer, 1024)) != -1)
    {
        if (nbytes > 0)
        {
            buffer[nbytes] = '\0';
            printf("client received:%s\n", buffer);
            bzero(buffer, 1024);
        }
    }
    close(sockfd);
    return 0;
}