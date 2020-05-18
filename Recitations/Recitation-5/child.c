#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Child: my PID is %d, and my parent is %d\n", getpid(), getppid());
}
