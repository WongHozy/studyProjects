#include <stdio.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
int num = 1;

void *fun1(void *arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("read num first = %d\n", num);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

void *fun2(void *arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("read num second = %d\n", num);
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
	}
}

void *fun3(void *arg)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		num++;
		printf("write thread first = %d\n", num);
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
	}
}

void *fun4(void *arg)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		num++;
		printf("write thread second = %d\n", num);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

int main()
{
	pthread_t ptd1, ptd2, ptd3, ptd4;

	pthread_rwlock_init(&rwlock, NULL);

	pthread_create(&ptd1, NULL, fun1, NULL);
	pthread_create(&ptd2, NULL, fun2, NULL);
	pthread_create(&ptd3, NULL, fun3, NULL);
	pthread_create(&ptd4, NULL, fun4, NULL);

	pthread_join(ptd1, NULL);
	pthread_join(ptd2, NULL);
	pthread_join(ptd3, NULL);
	pthread_join(ptd4, NULL);

	pthread_rwlock_destroy(&rwlock);

	return 0;
}
