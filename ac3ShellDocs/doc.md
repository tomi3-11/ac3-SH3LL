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
It can be found in the root.

