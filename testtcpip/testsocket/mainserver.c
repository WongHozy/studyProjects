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
	int socketfd, bindfd, listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[4096];
	int n;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);

	bindfd = bind(socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(bindfd == -1)
	{
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	listenfd = listen(socketfd, 10);
	if(listenfd == -1)
	{
		printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	while(1)
	{
		connfd = accept(socketfd, (struct sockaddr*)NULL, NULL);
		if(connfd == -1)
		{
			printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
			continue;
		}

		n = recv(connfd, buff, MAXLINE, 0);
		buff[n] = '\0';
		printf("recv msg from client: %s\n", buff);
		close(connfd);
	}

	close(socketfd);

	return 0;
}

