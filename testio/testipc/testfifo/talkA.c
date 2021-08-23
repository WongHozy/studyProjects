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
			perror("mkfifo1");
			goto err0;
		}
		printf("create mkfifo1\n");
	}

	ret = access("fifo2", F_OK);
	if(-1 == ret)
	{
		ret = mkfifo("fifo2", 0644);
		if(-1 == ret)
		{
			perror("mkfifo2");
			goto err0;
		}
		printf("create mkfifo2\n");
	}

	fdr = open("fifo1", O_RDONLY);
	if(-1 == fdr)
	{
		perror("open fifo1");
		goto err0;
	}
	printf("open fifo1 for reading ok...\n");

	fdw = open("fifo2", O_WRONLY);
	if(-1 == fdw)
	{
		perror("open fifo2");
		goto err0;
	}
	printf("open fifo2 for writing ok...\n");

	pid = fork();
	if(pid == -1)
	{
		perror("fork()");
		goto err1;
	}

	if(0 == pid)
	{
		while(1)
		{
			memset(buf, 0, SIZE);
			ret = read(fdr, buf, SIZE);
			if(ret <= 0)
			{
				perror("talkA read");
				break;
			}
			printf("\033[31mB: %s\033[0m\n", buf);
		}
		return 0;
	}

	while(pid > 0)
	{
		memset(buf, 0, SIZE);
		fgets(buf, SIZE, stdin);
		buf[strlen(buf)-1] = 0;

		ret = write(fdw, buf, strlen(buf));
		if(-1 == ret)
		{
			perror("talkA write");
			break;
		}
		printf("\033[96mA: %s\033[0m\n", buf);
	}

	close(fdr);
	close(fdw);

	return 0;

err1:
	close(fdr);
	close(fdw);
err0:
	return 1;
}

