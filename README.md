<div align="center">
  
![image](https://github.com/facetint/minishell/assets/99668549/00f5680d-417c-4369-b01f-a366555d3fa3)

</div>

# MINISHELL

## Shell Introduction

✣ In a shell, the user can run programs and also direct input from a file and output from a file.
    Bash allows users to enter commands and give instructions to the operating system.

## What Is Bash and How Does It Work?


![bahs](https://github.com/facetint/minishell/assets/99668549/9482ef70-4411-4efb-a871-2403ab33af95)


➤ *Bash is the shell, or command language interpreter, for the GNU operating system.*
➤ *Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`, which we replicated in our project.*
△ *At first sight bash appears to be a simple command/response system, where users enter commands and bash returns the results after those commands are run. However, bash is also a programming platform and users are enabled to write programs that accept input and produce output using shell commands in shell scripts.*



One of the most basic bash commands, ls, does one thing: list directory contents. By itself this command lists only the names of files and subdirectories in the current working directory.
  ## Prompt Display :

  Bash displays a "prompt" for the user to enter a command. Typically, this prompt contains the user name, computer name and working directory. The user can enter commands under this prompt.

<img width="892" alt="Ekran Resmi 2023-12-18 23 33 41" src="https://github.com/facetint/minishell/assets/99668549/d5399419-a858-4802-b4d7-b8f33b25a196">


  ## Command Input :

  The user can enter commands under prompt. These commands are used to perform system-related operations (file management, program execution, network operations, etc.)

  ## Command Interpreter :

  Bash interprets commands entered by the user. This means checking if the command is a defined program, processing the parameters if necessary and executing the command.

  ## Command Execution :

  It passes the interpreted command to the operating system through system calls and the operating system executes the command. For example, the ls command, a file listing command, requests the operating system to list files.

  ## Output and Error Checking : 

  After the command is executed, Bash checks whether the command completed successfully. If an error occurred, it displays error messages. It also reports the exit status of the command (0 if successful, or a different value if failed).

  ## History and Retrieval :

  It keeps a history of commands entered by the user and allows the user to access this history and undo previous commands. This is achieved with the arrow keys or the history command.

  ## Shell Scripts :

  Bash also allows users to create shell scripts that contain a sequence of commands. These scripts are used to automate specific tasks by stringing together sequential commands.

These basic steps of Bash provide a user-friendly command-line environment and come with a wide range of commands. Users can customize Bash and there is extensive documentation and community support.
  

## LEXER

▶︎ Its task is to decompose the commands entered by the user.

▶︎ It parses the input into symbols and tokens.

▶︎ For example, it takes the command "ls -l" and converts it into a delimited array like [ "ls", "-l" ].


## PARSER 

▶︎ Parses symbols and tokens from the lexer to understand the structure of commands.

▶︎ Creates the syntax tree. This tree represents the structure of the command in a hierarchical way.

▶︎ For example, it converts the command "ls -l" into a tree structure.


## EXPANDER

▶︎ Evaluates variables, wildcards and other special characters within the command.

▶︎ For example, it replaces "~" with home directory or matches "*" with file names.


## EXECUTE

▶︎ Starts a real process using a tree structure.

▶︎ Creates a new process using system calls such as fork and exec and executes the command specified in that process.

▶︎ Returns the result to the user.


## Useful shell utilities :


<img width="884" alt="Ekran Resmi 2023-12-24 02 00 35" src="https://github.com/facetint/minishell/assets/99668549/96413fde-0f58-4353-a8bf-ad7c6ef93644">


## Shell subset :


<img width="1149" alt="Ekran Resmi 2023-12-24 02 02 24" src="https://github.com/facetint/minishell/assets/99668549/3c889fb0-2727-4dca-bd88-d889304053ce">



## Shell features :


<img width="1149" alt="Ekran Resmi 2023-12-24 02 03 18" src="https://github.com/facetint/minishell/assets/99668549/96539ad5-74b5-43d8-8f1b-0bd95c8fb441">


## PIPE

EXAMPLE :


<img width="1323" alt="Ekran Resmi 2023-12-25 15 07 36" src="https://github.com/facetint/minishell/assets/99668549/9db762aa-dae4-47d0-971a-a770aa6976bf">



<img width="1225" alt="Ekran Resmi 2023-12-24 14 38 56" src="https://github.com/facetint/minishell/assets/99668549/2b0c9e5a-ca26-48b3-95de-bb416d03c85b">












## -EXAMPLE COMMANDS-

```  
cat | ls -l | wc -l

```
*prints the output and remains in the loop. We need to press enter.*


``` 
exit 23 45
```
*bash: exit: too many arguments*


``` 
cat << | wc -l
```
*bash: syntax error near unexpected token `|'*

``` 
aaa | bbb | aaa | aaa
```

*bash: aaa: command not found*

*bash: bbb: command not found*

*bash: aaa: command not found*

*bash: aaa: command not found*

``` 
cat file | cat << file
```
*only heredoc output is written*




