# Stage 1 of ac3 Shell
here we are not handling:
- arguments (`ls -l`)
- pipes
- redirection
- built-ins like `cd`
Only single-word external commands.

## Stage 1 Goal
User types:
```sh
ls
```
My shell:
1. Creates a child process
2. Child runs `/bin/sh`
3. Parent waits
4. Prompt returns

## New concepts introduced
| System Call | Purpose |
|-------------|---------|
| `fork()`    | create new process |
| `execvp()`  | run a program |
| `waitpid()` | parent waits for child |

Execution model:
```sh
ac3 (parent)
    |
    fork()
    |
child -> execvp("ls")
parent -> waitpid(child)
```
This is exactly how command execution works in:
- bash

### Now time for implementation
