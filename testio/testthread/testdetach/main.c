#include <stdio.h>
#include <pthread.h>

void *newthread()
{
	printf("new thread %lu start.\n", pthread_self());
	sleep(1);
	pthread_testcancel();
	printf("new thread testcancel1.\n");
	sleep(1);
	pthread_testcancel();
	printf("new thread testcancel2.\n");
	sleep(1);
	pthread_testcancel();
	printf("new thread testcancel3.\n");
	sleep(1);
	pthread_testcancel();
	printf("new thread testcancel4.\n");
	sleep(1);
	pthread_testcancel();
	printf("new thread testcancel5.\n");

	printf("new thread exit.\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, newthread, NULL);

	sleep(3);
	//printf("cancel new thread.\n");
	//pthread_cancel(tid);

	printf("detach thread.\n");
	pthread_detach(tid);

	//主线程退出，不会导致子线程退出
	printf("main thread %lu exit.\n", pthread_self());
	pthread_exit(NULL);
}
