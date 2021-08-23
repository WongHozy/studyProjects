
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("xxxx", "r");
	if(NULL == fp)
	{
		printf("error number: %d\n", errno);
		printf("error reason: %s\n", strerror(errno));
		perror("fopen err");
	}

	return 0;
}

