
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

/* IO
 * 文件描述符fd = open(文件路径及文件名pathname, 行为标志flags (, 无文件时创建文件权限设置mode))
 * 写入buf字节个数 = read(文件描述符fd, 内存首地址buf, 读取字节个数)
 * 移动字节数 = lseek(文件描述符fd, 偏移量offset, 移动起始位置whence)
 *
 * 文件描述符fd,默认为1024,其中0为标准输入、1为标准输出、2为标准错误（默认为/dev/tty文件,当前终端）
 *
 * 本地时间 = UTC时间 + 8h
 * ctime(t) == asctime(localtime(t))  获取本地时间
 * asctime(gmtime(t))  获取UTC时间
 *
 */

int main()
{
//open()读取数据
	int fd = open("./xxx", O_RDONLY | O_NONBLOCK);

	char buf[10];
	int ls, n;

	printf("文件描述符:%d\n", fd);
	ls = lseek(fd, 1, SEEK_CUR);
	n = read(fd, buf, sizeof(buf));
	if (n < 0)
	{
		if (errno != EAGAIN)
		{
			perror("read ./xxx");
			return -1;
		}
		printf("没有数据\n");
	}
	else
	{
		printf("有数据,");
		printf("移动%d位\n", ls);
		printf("data:%s\n", buf);
	}

	close(fd);

	printf("begin sleep 1 second.\n");
	sleep(1);
	printf("sleep end.\n");

//------------------------------------------------------
// 链接函数

	struct stat bufxxx;
	stat("xxx", &bufxxx);
	if(S_ISREG(bufxxx.st_mode))
	{
		printf("%s, st_mode = %d\n", "xxx是普通文件", bufxxx.st_mode);
		printf("xxx: 其他人权限:%d ", 0x0007 & bufxxx.st_mode);
		printf("所属组权限:%d ", (0x0038 & bufxxx.st_mode) >> 3);
		printf("所属者权限:%d ", (0x01C0 & bufxxx.st_mode) >> 6);
		printf("文件类型:%d\n", (0xF000 & bufxxx.st_mode) >> 12);
	}

	struct stat bufdir;
	stat("./", &bufdir);
	if(S_ISDIR(bufdir.st_mode))
	{
		printf("%s, st_mode = %d\n", "./是目录文件", bufdir.st_mode);
	}


//-------------------------------------------------------
// 目录函数

	char dirbuf[1000], *savebuf;
	savebuf = getcwd(dirbuf, 1000);
	printf("%d:%s\n%d:%s\n", dirbuf, dirbuf, savebuf, savebuf);

	DIR* dirp = opendir(dirbuf);
	if(dirp != NULL)
	{
		while(1)
		{
			struct dirent *dirinfo = readdir(dirp);
			if(dirinfo != NULL)
			{
				printf("d_name长度:%d  ", dirinfo->d_reclen);
				printf("d_type类型:%d  ", dirinfo->d_type);
				printf("d_name文件名:%s\n", dirinfo->d_name);
			}
			else
			{
				break;
			}
		}
	}
	int closeflag = closedir(dirp);
	if(closeflag == -1)
	{
		printf("closedir() fail.\n");
	}
	else
	{
		printf("closedir() success.\n");
	}

//----------------------------------------------------------
// 时间函数

	struct tm *atime = NULL;
	char *stime = NULL;

	time_t nowtime;
	nowtime = time(NULL);
	
	stime = ctime(&nowtime);
	if(stime == NULL)
	{
		perror("ctime");
	}
	else
	{
		printf("ctime: %s\n", stime);
		stime = NULL;
	}

	atime = gmtime(&nowtime);
	stime = asctime(atime);
	if(stime != NULL)
	{
		printf("gmtime asctime: %s\n", stime);
		stime = NULL;
	}

	atime = localtime(&nowtime);
	stime = asctime(atime);
	if(stime != NULL)
	{
		printf("localtime asctime: %s\n", stime);
		stime = NULL;
	}

	return 0;
}

