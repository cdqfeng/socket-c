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
#define MAX_SIZE 1024

int main()
{

	int sockfd, new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t sin_size;
	char msg[MAX_SIZE] = "Hello! ...\n";
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("this type int desc:%d", sockfd);
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //
	printf("the server addr is:%x", INADDR_ANY);
	server_addr.sin_port = htons(PORTNUM);
	int ret = bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
	ret = listen(sockfd, 5);
	while (1)
	{
		sin_size = sizeof(server_addr);
		new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size);
		fprintf(stderr, "Server get connection from %s\n", inet_ntoa(client_addr.sin_addr));
		ret = write(new_fd, msg, strlen(msg));
		while (1)
		{
			bzero(msg, MAX_SIZE);
			fgets(msg, MAX_SIZE, stdin);
			msg[strlen(msg) - 1] = '\0';
			printf("inputed: %s----input \"exit\" to quit\n", msg);
			if (strcmp(msg, "exit") == 0)
				break;
			ret = write(new_fd, msg, strlen(msg));
		}
		close(new_fd);
	}
	close(sockfd);
	return 0;
}