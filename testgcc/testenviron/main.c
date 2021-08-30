#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[])
{
	int i;
	for(i = 0; NULL != environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}

	printf("getenv(%s)=%s\n", "HOSTNAME", getenv("HOSTNAME"));

	return 0;
}
