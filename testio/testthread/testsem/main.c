#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;  //信号量

void printer(char *str)
{
	sem_wait(&sem);
	while(*str)
	{
		putchar(*str);
		fflush(stdout);
		str++;
		sleep(1);
	}
	printf("\n");
	sem_post(&sem);
}

void *thread_fun1(void *arg)
{
	char *str1 = "hello";
	printer(str1);
}

void *thread_fun2(void *arg)
{
	char *str2 = "world";
	printer(str2);
}

int main()
{
	pthread_t tid1, tid2;

	sem_init(&sem, 0, 1);

	pthread_create(&tid1, NULL, thread_fun1, NULL);
	pthread_create(&tid2, NULL, thread_fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	sem_destroy(&sem);

	return 0;
}
