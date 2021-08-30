#include <stdio.h>
#include <unistd.h>

/* execv()
 * 在实际应用中，通常调用execv()的都是子进程。
 * 人们之所以创建一个子进程，其目的就是执行一个与父进程代码不同的程序，而系统调用execv()就是子进程执行一个新程序的手段之一。
 * 
 * fork()的子进程: 独立的数据区和栈区、独立的系统堆栈区、共用的程序代码
 * execv()的子进程: 独立的程序代码，（完全独立的进程）
 *
 */

int main()
{
/*
	char *const argv[] = {"ps", "-au", NULL};
	char *const envp[] = {"PATH=/bin:usr/bin", "TERM=console", NULL};

	execl("/bin/ps", "ps", "-au", NULL);

	execlp("ps", "ps", "-au", NULL);

	execle("ps", "ps", "-au", NULL, envp);

	execv("/bin/ps", argv);

	execvp("ps", argv);

	execve("/bin/ps", argv, envp);
*/
	printf("-------------------------------------------------\n");

	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		printf("this is son process %d.\n", getpid());
		printf("execv() begin:\n");
		execv("./hello.out", NULL);
		printf("execv() end.\n");
	}
	else
	{
		printf("this is dad process %d.\n", getpid());
		printf("begin wait():\n");
		int sonStatus = 0, sonpid = 0;
		sonpid = wait(&sonStatus);
		if(-1 != sonpid)
		{
			printf("%d = wait(%d).\n", sonpid, sonStatus);
		}
	}

	return 0;
}
