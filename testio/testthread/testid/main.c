#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pthread_t thread_id;

	thread_id = pthread_self();
	printf("pid = %d\nThread ID = %lu\n", getpid(), thread_id);

	if(0 != pthread_equal(thread_id, pthread_self()))
	{
		printf("Thread Equal!\n");
	}
	else
	{
		printf("Thread Not Equal!\n");
	}

	return 0;
}
