#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

#define SHELL_MAX_INPUT 1024
#define MAX_ARGS 100


int main() {
    // size of the input string
    char input[SHELL_MAX_INPUT];

    while (1) {
        printf("Ac3 > ");
        fflush(stdout);

        if (fgets(input, SHELL_MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\r\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        // Tokenization stage
        char *argv[MAX_ARGS];
        int argc = 0;

        char *token = strtok(input, " ");

        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        argv[argc] = NULL;

        // Built in commands
        if (strcmp(argv[0], "exit") == 0) {
            printf("Existing ac3 shell\n");
            exit(0);
        }

        if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] == NULL) {
                fprintf(stderr, "cd: missing arguments\n");
            } else {
                if (chdir(argv[1]) != 0)
                    perror("cd failed");
            }
            continue;
        }

        if (strcmp(argv[0], "pwd") == 0){
            char cwd[PATH_MAX];

            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("pwd failed");

            continue;
        }

        // Redirection variables
        int input_redirect = 0;
        int output_redirect = 0;
        int append_redirect = 0;

        char *input_file = NULL;
        char *output_file = NULL;

        // Redirection parsing
        for (int i = 0; argv[i] != NULL; i++){
            if (strcmp(argv[i], "<") == 0) {
                input_redirect = 1;
                input_file = argv[i + 1];

                argv[i] = NULL;
            }

            else if (strcmp(argv[i], ">") == 0) {
                output_redirect = 1;
                output_file = argv[i + 1];

                argv[i] == NULL;
            }
            else if (strcmp(argv[i], ">>") == 0) {
                append_redirect = 1;
                output_file = argv[i + 1];

                argv[i] == NULL;
            }
        }

        // Fork 
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            continue;
        }

        // Child process
        if (pid == 0) {
            // Input redirection
            if (input_redirect) {
                int fd = open(input_file, O_RDONLY);

                if (fd < 0) {
                    perror("input file open failed");
                    exit(1);
                }

                dup2(fd, STDIN_FILENO);

                close(fd);
            }

            // OUTPUT REDIRECTION
            if (output_redirect) {
                int fd = open(
                output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (fd < 0) {
                    perror("output file open failed");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);

                close(fd);
            }

            // Append redirection
            if (append_redirect) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

                if (fd < 0) {
                    perror("append file open failed");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);

                close(fd);
            }

            execvp(argv[0], argv);

            perror("exec failed");
            exit(1);
        }

        // Parent process
        else {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
