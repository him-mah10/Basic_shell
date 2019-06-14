<h1 align="center"> C Shell</h1>

#### Author - Himanshu Maheshwari
Implementation of a C based bash shell using system calls

#### Getting Started
To run the shell, write:
    make
Followed by:
    ./a.out

#### Features
- Semicolon separated commands can be given as input. For e.g. echo hello ; ls -al will produce hello then the contents of the current directory.
- Bonus
	- Personal Reminder: It reminds you with a custom message after the given number of seconds elapse. The shell takes in commands during this time.
	- Clock Command: It displays dynamic date and time in shell withou using date or similar commands. It stops on press Ctrl+c or Ctrl+z. 
- Modularized code
  - Uses makefile for compilation process
  - All header files and declarations in header.h
- Implements both Foreground and Background process and displays a message when background process ends.
- It has commands implemented by me like: ls, echo, pwd, exit, pinfo, setenv, unsetenv, jobs, kbjob, fg, bg, overkill and quit. Pinfo prints process related to shell or based on given pid.
- Colors are used wherever it was necessary to make output readable and pretty.
- It includes all the features as needed in the assignements.
- CTRL-Z and CTRL-C are also implemented as per specifications.
- Redirection, piping and piping with redirection is implemented and is self made.
- Shell is as close as real shell in all aspects.

#### Cheers!!!
