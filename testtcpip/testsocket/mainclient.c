#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
	int sockfd, connfd;
	char recvline[MAXLINE], sendline[MAXLINE];
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		printf("usage: ./client <ipaddress>\n");
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);

	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	connfd = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(connfd < 0)
	{
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	printf("send msg to server: \n");
	fgets(sendline, MAXLINE, stdin);
	send(sockfd, sendline, strlen(sendline), 0);

	close(sockfd);
	exit(0);

	return 0;
}
