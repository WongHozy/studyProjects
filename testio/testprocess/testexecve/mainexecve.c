
#include <unistd.h>

int main()
{
	char *const argv[] = {"ps", "-au", NULL};
	char *const envp[] = {"PATH=/bin:usr/bin", "TERM=console", NULL};

	execl("/bin/ps", "ps", "-au", NULL);

	execlp("ps", "ps", "-au", NULL);

	execle("ps", "ps", "-au", NULL, envp);

	execv("/bin/ps", argv);

	execvp("ps", argv);

	execve("/bin/ps", argv, envp);

	return 0;
}
