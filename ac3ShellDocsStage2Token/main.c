#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

int main(){
	char input[MAX_INPUT];

	while (1){
		printf("ac3 > ");
		fflush(stdout);

		if (fgets(input, MAX_INPUT, stdin) == NULL){
			printf("\n");
			break;
		}

		// Removing the new lines
		input[strcspn(input, "\r\n")] = '\0';

		if (strlen(input) == 0) continue;

		// Start Tokenization
		char *argv[MAX_ARGS];
		int argc = 0;

		char *token = strtok(input, " ");

		while (token != NULL && argc < MAX_ARGS -1) {
			argv[argc++] = token;
			token = strtok(NULL, " ");
		}

		argv[argc] = NULL;
		
		pid_t pid = fork();

		if (pid < 0){
			perror("fork failed");
			continue;
		}

		if (pid == 0) {
			execvp(argv[0], argv);
			perror("exec failed");
			exit(1);
		} else {
			waitpid(pid, NULL, 0);
		}
	}

	return 0;
}


