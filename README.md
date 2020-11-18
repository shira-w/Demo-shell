# Demo-shell
A self-made shell, CMD of Linox

The goal of this assignment is to gain experience with process management, pipes, signals, and the
relevant system calls. To do this, you will implement a simple shell program. You will implement
the function that receives a shell command and performs it. We provide a skeleton shell program
(shell.c), which reads lines from the user, parses them into commands, and invokes your function.
You also have to implement any initialization/finalization code that you require (more details below).
The goal of this assignment is to gain experience with process management, pipes, signals, and the
relevant system calls. To do this, you will implement a simple shell program. You will implement
the function that receives a shell command and performs it. We provide a skeleton shell program
(shell.c), which reads lines from the user, parses them into commands, and invokes your function.
You also have to implement any initialization/finalization code that you require (more details below).

The skeleton we provide executes an infinite loop. Each iteration does the following:
1. Reads a string containing a shell command from standard input. If Ctrl-D is pressed, the skeleton
exits.
2. Parses the command string into an array of words. A word is a non-empty sequence of nonwhitespace
characters, where whitespace means space, tab (\t), or newline (\n). The end of the
array is designated with a NULL entry.
3. Invokes your function, passing it the parsed command line array. The skeleton detects and ignores
empty lines (i.e., won’t invoke your function on an empty command).
1.2 Shell functionality
The shell will support the following operations, which are described in more detail in Section 2.2:
1. Executing commands. The user enters a command, i.e., a program and its arguments, such as
sleep 10. The shell executes the command and waits until it completes before accepting another
command.
2. Executing commands in the background. The user enters a command followed by &, for
example: sleep 10 &. The shell executes the command but does not wait for its completion
before accepting another command.
1
3. Single piping. The user enters two commands separated by a pipe symbol (|), for example:
cat foo.txt | grep bar. The shell executes both commands, piping the output of the first
command to the input of the second command. The shell waits until both commands complete
before accepting another command.
The shell doesn’t need to support built-in commands such as cd and exit. It only support
execution of program binaries as described above.

----------------------------------------------------------------------
Enjoy it.

###### do you have some comments, negative or positive review? I would like to hear you: 

###### shirawein70@gmail.com
