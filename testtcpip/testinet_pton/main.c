#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* inet_aton()
 * 地址 转 二进制数值
 *
 * inet_addr()
 * 二进制数值 转 地址
 */
int main()
{
	char ip[20] = {"127.0.0.1"};
	int port = 8080;
	struct in_addr addr;

	inet_pton(AF_INET, ip, (void*)&addr);
	printf("inet_pton: 0x%x\n", addr.s_addr);
	printf("inet_pton: %d\n", addr.s_addr);

	inet_ntop(AF_INET, (void*)&addr, ip, 16);
	printf("inet_ntop: %s\n", ip);

	return 0;
}
