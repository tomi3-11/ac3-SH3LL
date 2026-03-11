# stage 2 part 2 (Tokenization)
Here we simply implement a large size argument to accomodate more than one argument in my shell

Now we currently have the following and working;
- fork()
- execvp()
- waitpid()
- newline cleanup
But currently this fails:
```sh
ls -l
echo hello world
mkdir test
```
Because my shell is passing the entire line as one argument

### Now stage 2 fixes
## Stage 2 Goal
we gonna Convert this:
```text
"ls -ls"
```
Into this:
```c
["ls", "-l", NULL]
```

And then this as well;
```text
"echo hello world"
```
into thw following
```c
["echo", "hello", "world", NULL]
```
The above array is what `execvp()` expects.

## Concept: Tokenization
Here we gonna split the inputs by spaces <br>
Now this where we use this
```c
strtok()
```
This modifies the input buffer in place and returns tokens one by one.

### What changes has been added
i added:
```c
char *argv[MAX_ARGS];
```
instead of:
```c
char *argv[] = { input, NULL };
```
Now this builds a proper argument array.

### stage 2 Test Checklist
These must work.
```bash
ls -l
ls -a
pwd
echo hello
echo hello world
mkdir testdir
rm testdir
```
But these don't work right now
```bash
cd ..
ls > file.txt
ls | wc
sleep 5 &
```
Or in other words it is gonna show you an error if used right now
