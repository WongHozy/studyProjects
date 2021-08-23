#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 0x100000

void *th_fun(void *arg)
{
/* fork
 * 应避免在多线程中调用fork，除非马上exec
 * 子进程中只有调用fork的线程存在，其他线程在子进程中均 pthread_exit()
 */

	while(1)
	{
		sleep(1);
		printf("thread %lu run.\n", pthread_self());
	}
}

int main()
{
	pthread_t tid;
	int err, detachstate, i = 1;

	pthread_attr_t attr;
	size_t stacksize;
	void *stackaddr;

	printf("main thread %lu\n", pthread_self());

	pthread_attr_init(&attr);
	pthread_attr_getstack(&attr, &stackaddr, &stacksize);
	pthread_attr_getdetachstate(&attr, &detachstate);


	if(detachstate == PTHREAD_CREATE_DETACHED)
	{
		printf("thread detached\n");
	}
	else if(detachstate == PTHREAD_CREATE_JOINABLE)
	{
		printf("thread join\n");
	}
	else
	{
		printf("thread unknown\n");
	}
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	while(i < 6)
	{
		stackaddr = malloc(SIZE);
		if(stackaddr == NULL)
		{
			perror("malloc");
			exit(1);
		}

		stacksize = SIZE;
		pthread_attr_setstack(&attr, stackaddr, stacksize);
		err = pthread_create(&tid, &attr, th_fun, NULL);
		if(err != 0)
		{
			printf("%s\n", strerror(err));
			exit(1);
		}
		printf("create thread %d\n", i++);
		sleep(2);
	}

	pthread_attr_destroy(&attr);
	
	//主线程退出，其他线程不退出，主线程应调用 pthread_exit()
	pthread_exit(NULL);
	//return 0;
}
