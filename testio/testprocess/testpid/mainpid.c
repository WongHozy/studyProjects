#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int a = 10;

/* 父子进程
 * fork()函数，子进程是父进程的一个复制品:
 * * 上下文、进程堆栈、打开的文件描述符、信号控制设定、进程优先级、进程组号
 * * 栈区、堆区、BSS区、数据区、代码区
 * * 子进程独有: 进程号、计时器
 *
 * fork()函数代价很大
 */

int main()
{
	int b = 20;
	pid_t fpid;
	fpid = fork();
	if(fpid < 0)
	{
		perror("fork()");
		return -1;
	}

	if(0 == fpid)
	{
		a = 111;
		b = 222;
		printf("son process: a = %d, b = %d\n", a, b);
	}
	else if(fpid > 0)
	{
		sleep(1);
		printf("dad process: a = %d, b = %d\n", a, b);
	}

	_exit(0);

	return 0;
}
