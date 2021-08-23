#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int a = 10;

/* 父子进程
 * fork()函数，子进程是父进程的一个复制品:
 * * 上下文、进程堆栈、打开的文件描述符、信号控制设定、进程优先级、进程组号
 * * 栈区、堆区、BSS区、数据区、代码区
 * * 子进程独有: 进程号、计时器
 *
 * fork()函数代价很大
 *
 * _exit(x): 返回父进程参数(从第8位开始)
 *
 * wait(): 得到子进程退出状态,并彻底清除掉子进程资源
 * waitpid(x, y, z):
 * 若z为WNOHANG,没有任何已经结束的子进程,则立即返回.
 * 若z为0,则与wait()一样阻塞父进程,等待子进程退出.
 *
 * 子进程终止,父进程尚未回收,子进程残留资源在内核中, 变成了僵尸进程
 * 父进程终止,子进程未终止,子进程变成了孤儿进程
 *
 */

int main()
{
	int b = 20;
	pid_t fpid = 1;
	fpid = fork();
	if(fpid < 0)
	{
		perror("fork()");
		return -1;
	}
	printf("fpid = %d\n", fpid);

	if(0 == fpid)
	{
		a = 111;
		b = 222;
		pid_t pid = getpid();
		printf("son process: pid = %d,  a = %d, b = %d\n", pid, a, b);
	}
	else if(fpid > 0)
	{
		int sonStatus;
		pid_t sonPid, pid;
		sonPid = waitpid(fpid, &sonStatus, 0);
		pid = getpid();
		printf("dad process: sonProcess end, sonPid = %d, sonStatus = %d\n", sonPid, sonStatus);
		printf("dad process: pid = %d, a = %d, b = %d\n", pid, a, b);
	}

	_exit(1);

	return 0;
}
