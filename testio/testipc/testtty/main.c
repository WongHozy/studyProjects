#include <stdio.h>
#include <unistd.h>

/* 终端
 * 在UNIX系统中，用户通过终端登录系统后得到一个Shell进程，终端成为Shell进程的控制终端
 *
 */ 
int main()
{
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	return 0;
}
