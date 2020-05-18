#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t pid = fork();

	if(pid == -1) 
		printf("Error: fork failed!");
	else if(pid == 0)
		execl("./child", "./child",  NULL);
	else {
		wait(0);
		printf("Parent: my PID is %d\n", getpid());
	}
}
