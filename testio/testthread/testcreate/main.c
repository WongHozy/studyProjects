#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void* thread_fun(void *arg)
{
	static int ret = 123;

	sleep(1);
	int num = *((int*)arg);
	printf("in the new thread: num = %d\n", num);

	pthread_exit((void*)&ret);
	//return &ret;
}

/* perror不能使用
 *
 *
 */
int main()
{
	pthread_t tid, cid;
	int test = 100;

	tid = pthread_self();
	int ret = pthread_create(&cid, NULL, thread_fun, (void*)&test);
	if(ret != 0)
	{
		printf("error number: %d\n", ret);
		printf("error information: %s\n", strerror(ret));
	}
	else
	{
		printf("init pid = %d\n", getpid());
		printf("init thread id = %lu\n", tid);
		printf("crate thread id = %lu\n", cid);
	}

	void *retval = NULL;
	ret = pthread_join(cid, &retval);
	if(ret == 0)
	{
		printf("retval = %d\n", *((int*)retval));
	}

	return 0;
}

