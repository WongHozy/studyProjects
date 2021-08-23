#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>  //struct sigaction
#include <sys/types.h>
#include <sys/time.h>  //struct itimerval
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>  //strlen(x)

/* open()函数包含头文件:
 * <sys/types.h>
 * <sys/stat.h>
 * <fcntl.h>
 */

void write_time(int num)
{
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	char *cur = ctime(&rawtime);

	//printf("%s\n", cur);

	int fd = open("/tmp/timelog.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}

	int ret = write(fd, cur, strlen(cur) + 1);
	if(ret == -1)
	{
		perror("write error");
		exit(1);
	}

	close(fd);
}

int main(int argc, const char* argv[])
{
	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}

	if(pid > 0)
	{
		exit(1);
	}
	else if(pid == 0)
	{
		setsid();

		chdir("/tmp");

		umask(0022);

		//close(STDIN_FILENO);
		//close(STDOUT_FILENO);
		//close(STDERR_FILENO);

		//注册信号捕捉函数
		struct sigaction sigact;
		sigact.sa_flags = 0;
		sigemptyset(&sigact.sa_mask);
		sigact.sa_handler = write_time;
		sigaction(SIGALRM, &sigact, NULL);

		//设置定时器
		struct itimerval act;
		act.it_interval.tv_sec = 2;
		act.it_interval.tv_usec = 0;
		act.it_value.tv_sec = 2;
		act.it_value.tv_usec = 0;

		//开始计时
		setitimer(ITIMER_REAL, &act, NULL);

		while(1);
	}


	return 0;
}
