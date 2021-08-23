#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pgid, pid, ppid;

	pid = getpid();
	ppid = getppid();
	pgid = getpgrp();
	printf("getpid() = %d\n", pid);
	printf("getppid() = %d\n", ppid);
	printf("getpgrp() = %d\n", pgid);
	printf("getpgid(%d) = %d\n", pid, getpgid(pid));

	//改变进程所属的进程组为 父进程的进程组
	int ret = setpgid(pid, ppid);
	if(ret == 0)
	{
		printf("\nsetpgid(%d, %d)\n", pid, ppid);
		pid = getpid();
		ppid = getppid();
		pgid = getpgrp();
		printf("getpid() = %d\n", pid);
		printf("getppid() = %d\n", ppid);
		printf("getpgrp() = %d\n", pgid);
		printf("getpgid(%d) = %d\n", pid, getpgid(pid));
	}
	else
	{
		perror("setpgid");
	}

	return 0;
}
