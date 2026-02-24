#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT 1024

int main() {
	char input[MAX_INPUT];

	while (1) {
		printf("ac3> ");
		fflush(stdout);

		if (fgets(input, MAX_INPUT, stdin) == NULL) {
			printf("\n");
			break;
		}

		// Remove new line character
		input[strcspn(input, "\n")] = '\0';

		// Skip empty inputs
		if (strlen(input) == 0)
			continue;

		char *exitOut = "exit";

		if (strcmp(input, exitOut) == 0)
			break;

		pid_t pid = fork();

		if (pid < 0) {
			perror("fork failed");
			continue;
		}

		if (pid == 0) {
			char *argv[] = { input, NULL };
			execvp(argv[0], argv);
			perror("exec failed");
			exit(1);
		} else {
			waitpid(pid, NULL, 0);
		}


	}
	return 0;
}
