#include <stdio.h>
#include <arpa/inet.h>

/* u_short = htons(u_short)
 * 大尾顺序
 * 小尾顺序
 *
 * 增加可移植性
 */
int main()
{
	int a = 16, b;

	b = htons(a);

	printf("a = %d\n", a);
	printf("b = %d\n", b);

	return 0;
}
