
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


int main()
{
	struct stat st;
	int ret;
	ret = stat("./", &st);
	if(ret == -1)
	{
		perror("stat");
		return -1;
	}

	char perms[11] = {0};

	switch(st.st_mode & S_IFMT)
	{
		case S_IFSOCK:  //套接字
			perms[0] = 's';
			break;
		case S_IFLNK:  //符号链接(软链接)
			perms[0] = 'l';
			break;
		case S_IFREG:  //普通文件
			perms[0] = '-';
			break;
		case S_IFBLK:  //块设备
			perms[0] = 'b';
			break;
		case S_IFDIR:  //目录
			perms[0] = 'd';
			break;
		case S_IFCHR:  //字符设备
			perms[0] = 'c';
			break;
		case S_IFIFO:  //管道
			perms[0] = 'p';
			break;
		default:
			perms[0] = '?';
			break;
	}
	perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
	perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
	perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
	perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

	int linkNum = st.st_nlink;
	char *fileUser = getpwuid(st.st_uid)->pw_name;
	char *fileGrp = getgrgid(st.st_gid)->gr_name;
	int fileSize = (int)st.st_size;
	char *time = ctime(&st.st_mtime);

	char mtime[512] = {0};
	strncpy(mtime, time, strlen(time)-1);

	char buf[1024];
	sprintf(buf, "%s %d %s %s %d %s %s", perms, linkNum, fileUser, fileGrp, fileSize, mtime, "./");

	printf("%s\n", buf);

	return 0;
}

