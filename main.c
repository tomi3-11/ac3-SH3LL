#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 1024

int main() {
	char input[MAX_INPUT];

	while (1){
		// Print prompt
		printf("ac3 >");
		fflush(stdout);

		// Read input from user
		if (fgets(input, MAX_INPUT, stdin) == NULL){
			printf("\n");
			break;
		}
	}
	return 0;
}
