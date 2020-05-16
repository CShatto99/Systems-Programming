#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOK_DELIM " \t\r\n\a"

int main() {
	char input[100];
	char **args = malloc(64 * sizeof(char*));
	char *token;
	int index;

	while(1) {
		printf("$ ");
		fgets(input, sizeof(input), stdin); // store the current input line into one string

		index = 0;
		token  = strtok(input, TOK_DELIM); // get the first word from the input
		
		while(token != NULL) { // store each word from the input into an arguments array
			args[index++] = token;
			token = strtok(NULL, TOK_DELIM);
		}
		args[index] = NULL; // make the last element in the arguments array NULL (required for execvp)

		pid_t pid = fork();

		if(pid == -1)
			printf("Error: fork failed.\n");
		else if(pid == 0) { // child process
			execvp(args[0], args);
			printf("%s: command not found\n", input);
		}
		else // parent process
			wait(0);
	}
	free(args);
	return 0;
}
