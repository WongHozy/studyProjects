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

	/* 一个文件或者其他对象映射进内存
	 * addr: NULL
	 * length: 映射到内存的文件长度
	 * prot: 映射区保护方式, 读/写
	 * flags: MAP_SHARED复制文件, MAP_PRIVATE写入
	 * fd: 要映射的文件描述符
	 * offset: 文件其实偏移
	 */
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
	{
		perror("mmap error");
		return -1;
	}

	close(fd);

	printf("buf = %s\n", (char*)ptr);

	strcpy((char*)ptr, "this is a test");

	int ret = munmap(ptr, len);  //释放内存映射区
	if(ret == -1)
	{
		perror("munmap error");
		return -1;
	}

	return 0;
}
