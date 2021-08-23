#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 128

int main()
{
	int ret = -1, fdr = -1, fdw = -1;
	pid_t pid = -1;
	char buf[SIZE];

	ret = access("fifo1", F_OK);
	if(-1 == ret)
	{
		ret = mkfifo("fifo1", 0644);
		if(-1 == ret)
		{
			perror("mkfifo fifo1");
			return -1;
		}
		printf("create fifo1\n");
	}

	ret = access("fifo2", F_OK);
	if(-1 == ret)
	{
		ret = mkfifo("fifo2", 0644);
		if(-1 == ret)
		{
			perror("mkfifo fifo2");
			return -1;
		}
		printf("create fifo2\n");
	}

	fdw = open("fifo1", O_WRONLY);
	if(fdw == -1)
	{
		perror("open fifo1");
		return -1;
	}
	printf("open fifo1 for writing ok...\n");

	fdr = open("fifo2", O_RDONLY);
	if(fdr == -1)
	{
		perror("open fifo2");
		return -1;
	}
	printf("open fifo2 for reading ok...\n");

	pid = fork();
	if(pid == -1)
	{
		perror("fork()");
	}

	while(pid == 0)
	{
		memset(buf, 0, SIZE);
		ret = read(fdr, buf, SIZE);
		if(ret <= 0)
		{
			perror("talkB read");
			break;
		}
		printf("\033[31mA: %s\033[0m\n", buf);
	}

	while(pid > 0)
	{
		memset(buf, 0, SIZE);
		fgets(buf, SIZE, stdin);
		buf[strlen(buf)-1] = 0;

		ret = write(fdw, buf, strlen(buf));
		if(-1 == ret)
		{
			perror("talkB write");
			break;
		}
		printf("\033[96mB: %s\033[0m\n", buf);
	}

	close(fdw);
	close(fdr);

	return 0;
}
