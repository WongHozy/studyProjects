#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd = open("xxx.txt", O_RDWR);
	int len = lseek(fd, 0, SEEK_END);  //返回偏移量

	printf("xxx.txt len = %d\n", len);

	//一个文件或者其他对象映射进内存
	//len: 映射到内存的文件长度
	//fd: 要映射的文件描述符
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
	{
		perror("mmap error");
		return -1;
	}
	close(fd);

	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(1);
		printf("%d: %s\n", pid, (char*)ptr);
		strncpy((char*)ptr, "i am your son.", len);
	}
	else if(pid > 0)
	{
		strncpy((char*)ptr, "i am your dad.", len);
		wait(NULL);
		printf("%d: %s\n", pid, (char*)ptr);
	}

	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap error.");
		return -1;
	}

	return 0;
}
