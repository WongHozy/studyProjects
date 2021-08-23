
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// 进程

int main()
{
	pid_t pid = getpid();
	printf("pid = %d\n", pid);	

	pid_t ppid = getppid();
	printf("ppid = %d\n", ppid);

	pid_t pgid = getpgid(pid);
	printf("pgid = %d\n", pgid);

//---------------------------------------

	pid_t fpid;
	fpid = fork();
	if(fpid < 0)
	{
		perror("fork");
		return -1;
	}

	if(0 == fpid)
	{
		while(1)
		{
			printf("I am son process:%d\n", fpid);
			sleep(1);
		}
	}
	else if(fpid > 1)
	{
		while(1)
		{
			printf("I am dad process:%d\n", fpid);
			sleep(1);
		}
	}

	return 0;
}


