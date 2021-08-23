
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

// ./main.out "hello" "world"
/*输出:
 * ./main.out
 * hello
 * world
 * 60.000000, 0.500000
 */

int main(int argc, char* argv[])
{
	int i;
        for(i = 0; i < argc; i++)
        {
                printf("%s\n", argv[i]);
        }

	double param, result;
	param = 60.0;
	result = cos(param * PI / 180.0);

	printf("%f, %f\n", param, result);

	return 0;
}

