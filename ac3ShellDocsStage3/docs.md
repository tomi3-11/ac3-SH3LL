# Stage 3 dealing with built-in commands
we continue building our shell, right now our shell works but some built-in commands fail, so lets deal with them

Lets have a recap of what we achieved so far
- read user input
- tokenize commands
- execute external programs using `fork()` + `execvp()`
- wait for child processes

However, something import still does not work:
```sh
cd ..
```
or 
```sh
exit
```
Now this opens the next stage: `3`

## Stage 3 goals - Built-in Commands
Some commands cannot be executed using `execvp()`.<br>
These must run inside the shell process itself.

We call them **Built-ins**.<br>
Examples.

| Commands | Why is it Built-in |
|----------|--------------------|
| `cd`     | Must change the shell's working directory |
| `exit`   | Must terminate the shell process |
| `pwd`    | Can be implemented internally |

### Why `cd` Cannot Use `exec()`
Suppose we tried this:
```bash
cd ..
```
Execution with Stage 2 logic would be:
```sh
fork()
child -> execvp("cd")
```
But two problems occur:<br>
1. `cd` is not a program
There is not executable
```sh
/bin/cd
```
2. Even if it existed
The child process would change its directory. But the parent shell would remain/stay in the same directory.<br>
Example:
```sh
ac3 (parent) -> /home/user
child executes cd ..
child exits
```
Parent directory stays unchanged

Therefore:
> The shell itself must call `chdir()`

### Here are the built-ins that will be added
| Command | Implementation |
|---------|----------------|
| `cd`    | `chdir()`      |
| `exit`  | `exit()`      |
| `pwd`   | `getcwd()`      |

### Where the builts-ins will go in the current flow
Current Flow
```sh
read input
tokenize
fork
exec
wait
```
New flow
```sh
read input
tokenize

if built-in
    run builtin
else
    fork
    exec
    wait
```
Built-ins  must be checked before fork

## Stage 3 test checklists
These must work
```sh
pwd
cd ..
pwd
cd /
pwd
exit
```
External commands must still work:
```sh
ls
ls -l
echo hello
date
```
This is it for stage 3
