#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// kill: 给指定进程发送指定信号(不一定杀死)
int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		int i = 0;
		for(i = 0; i < 10; i++)
		{
			printf("pid = %d, son process %d\n", pid, getpid());
			sleep(1);
		}
	}

	if(pid > 0)
	{
		printf("pid = %d, father process %d\n", pid, getpid());
		sleep(3);
		printf("kill my son process now.\n");
		kill(pid, SIGINT);

		sleep(2);
		printf("pid = %d, father process %d will end.\n", pid, getpid());
	}

	return 0;
}
