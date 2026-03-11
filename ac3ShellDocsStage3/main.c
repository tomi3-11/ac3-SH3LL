#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#define SHELL_MAX_INPUT 1024
#define MAX_ARGS 100


int main(){
    char input[SHELL_MAX_INPUT];

    while (1){
        printf("ac3 > ");
        fflush(stdout);

        if (fgets(input, SHELL_MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\r\n")] = '\0';

        if (strlen(input) == 0) continue;

        // Tokenization
        char *argv[MAX_ARGS];
        int argc = 0;

        char *token = strtok(input, " ");

        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        argv[argc] = NULL;

        // Build in commands implementation
        // Here we are going to have a exit
        if (strcmp(argv[0], "exit") == 0) {
            printf("Exiting ac3 shell\n");
            exit(0);
        }

        // For cd
        if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(argv[1]) != 0) {
                    perror("cd failed");
                }
            }
            continue;
        }

        // For pwd
        if (strcmp(argv[0], "pwd") == 0) {
            char cwd[PATH_MAX];

            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("pwd failed");

            continue;
        }

        // External commands
        pid_t pid = fork();

        if (pid < 0) {
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
