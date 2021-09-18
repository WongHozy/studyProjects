
#include <stdio.h>
#include <errno.h>
#include <string.h>

void DealFile(FILE *rfp, FILE *wfp);

int main()
{
	FILE *rfp = fopen("B97F_B8DD.txt", "r");
	FILE *wfp = fopen("CheckSinr.txt", "a");

	if(nullptr == rfp || nullptr == wfp)
	{
		printf("error number: %d\n", errno);
		printf("error reason: %s\n", strerror(errno));
		perror("fopen err");
		return 0;
	}
	else
	{
		printf("open file success.\n");
		DealFile(rfp, wfp);
	}

	fclose(rfp);
	fclose(wfp);

	return 0;
}

void DealFile(FILE *rfp, FILE *wfp)
{
	char buff[1024000];
	char *foundDD = nullptr, *found7F = nullptr;

	while(fgets(buff, 1024000, rfp) != nullptr)
	{

		foundDD = strstr(buff, "DD B8");
		found7F = strstr(buff, "7F B9");

		if(foundDD == nullptr && found7F == nullptr)
		{
			continue;
		}
		else
		{
			fputs(buff, wfp);
		}
	}

	fflush(wfp);
}









