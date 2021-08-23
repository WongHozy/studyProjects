
#include <glib.h>

int main()
{
	gchar a[20], b[20];

	//a = "123456";

	g_print("hello world\n");

	g_stpcpy(a, "123456");

	g_print("%s\n", a);

	g_stpcpy(b, a);

	g_print("b:%s\n", b);

	return 0;
}
