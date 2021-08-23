#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* exit()  <stdlib.h>
 * _exit()  <unistd.h>
 *
 * 停止进程运行，清除其使用的内存空间，销毁其在内核中的数据结构
 * 另外: exit()还把文件缓冲区中的内容写回文件，"清理I/O缓冲"
 */
int main()
{
	pid_t pid, ppid, pgid, sid;

	pid = getpid();
	ppid = getppid();
	pgid = getpgrp();
	sid = getsid(pid);
	printf("getpid() = %d\n", pid);
	printf("getppid() = %d\n", ppid);
	printf("getpgrp() = %d\n", pgid);
	printf("getsid(%d) = %d\n", pid, sid);

	pid_t fpid;
	fpid = fork();
	if(fpid == 0)
	{
		//sleep(1);
		printf("create process pid = %d\n", getpid());
		printf("ppid = %d\n", getppid());
		printf("pgid = %d\n", getpgrp());
		printf("sid = %d\n", getsid(getpid()));

		/* 创建一个会话
		 * 新进程组ID = 自己进程ID
		 * 新会话ID = 自己进程ID
		 * 父进程ID = 1（init进程）
		 */
		printf("setsid():\n");
		pid_t ret = setsid();
		if(ret != -1)
		{
			printf("pid = %d\n", getpid());
			printf("ppid = %d\n", getppid());
			printf("pgid = %d\n", getpgrp());
			printf("sid = %d\n", getsid(getpid()));
		}

		exit(1);
	}
	else
	{
		printf("exit %d process.\n", getpid());
		exit(1);
	}

	return 0;


}
