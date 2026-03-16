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

We call them **Built-ins**.

