# Ace Shell
Here am trying to build a mini shell in c 

I have to do is to build a shell that:
- shows a prompt
- waits for inputs
- stores the input in memory
- loops forever

Nothing else 

## Stage 0 goal
I should see this:
```sh 
ac3 >
```
Then i should type this:
```sh
hello
```
Press enter ->

Then the shell should prompt me again:
```sh 
ac3 >
```
It does not execute anything yet.

Here we are only proving that, `The shell can read commands into a buffer`.

### Core Concept: Input Buffer
When user types:
```sh
ls -l
```
The OS sends that to my shell through:
```sh
stdin (file descriptor 0)
```
Now I must:
1. Allocate memory
2. Read from stdin
3. Store it in a character array


## Implementation
Here is the full implementation
```c
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
```
### What is Happening here?
1. Buffer Creation
```c
char input[MAX_INPUT];
```
I am reserving 1024 bytes in memory. User input goes here
2. Infinite Shell Loop
```c
while (1)
```
Shells never stop unless user exits.
3. Prompt Display
```c
printf("ac3 > ");
fflush(stdout);
```
We flush because `printf` is buffered. Without this prompt may not show immediately.
4. Reading Input
```c
fgets(input, MAX_INPUT, stdin)
```
Reads:
- from keyboard
- until Enter
- or buffer fills

Example stored in memory:
```sh
l  s    - l \n \0
```
The `\n` will matter later for parsing.

## Compile & Run
```sh
# compiling the c program
gcc main.c -o ac3Shell

# Running the program
./ac3Shell
```
Test:
- Type anything
- Shell should not crash
- Shell should loop forever

Exit with:
```sh
ctrl + D
```
