<div align="center">
  
![image](https://github.com/facetint/minishell/assets/99668549/20e35f8f-8026-49b6-b46c-7b08eafb41d5)


</div>

## Table of Contents
- [Shell Introduction](#shell-introduction)
  - [What Is Bash and How Does It Work?](#what-is-bash-and-how-does-it-work)
- [Algoritm](#algoritm)
  - [State Machines](#state-machines)
- [Implementation](#implementation)
  - [Lexer](#the-lexer)
  - [Parser](#the-parser)
  - [Expander](#expander)
  - [Executor](#executor)
  - [Builtin](#builtin)
      - [exit](#exit)
      - [cd](#cd)
      - [export](#export)
      - [unset](#unset)
      - [pwd](#pwd)
      - [echo](#echo)
      - [env](#env)
  - [Signals](#signals)
  - [Example Commands](#example-commands)
  - [Pipe](#pipe)
- [Installation](#installation)

## Shell Introduction

✣ In a shell, the user can run programs and also direct input from a file and output from a file.
    Bash allows users to enter commands and give instructions to the operating system.

## What Is Bash and How Does It Work?


![bahs](https://github.com/facetint/minishell/assets/99668549/9482ef70-4411-4efb-a871-2403ab33af95)


➤ *Bash is the shell, or command language interpreter, for the GNU operating system.*

➤ *Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`, which we replicated in our project.*

△ *At first sight bash appears to be a simple command/response system, where users enter commands and bash returns the results after those commands are run. However, bash is also a programming platform and users are enabled to write programs that accept input and produce output using shell commands in shell scripts.*
*One of the most basic bash commands, ls, does one thing: list directory contents. By itself this command lists only the names of files and subdirectories in the current working directory.*


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






### **ALGORITM**


![minishell-plan](https://github.com/facetint/minishell/assets/99668549/5d95d53a-b022-4547-9478-da55f6ffad94)


**When we wrote this project, we were inspired by state machines.**




#### STATE MACHINE 


  *The basic building blocks of a state machine are states and transitions. A state is a situation of a system depending on previous inputs and causes a reaction on following inputs. One state is marked as the initial state; this is where the execution of the machine starts. A state transition defines for which input a state is changed from one to another. Depending on the state machine type, states and/or transitions produce outputs.*


![state-machine-example](https://github.com/facetint/minishell/assets/99668549/a5263d1a-815e-4f7c-a977-2298fb066e2c)

## Tokenization
This minishell project uses these tokens:

      DOUBLE_QUOTED_WORD
      SINGLE_QUOTED_WORD
      UNQUOTED_WORD
      PIPE
      OUTPUT_REDIRECTION
      INPUT_REDIRECTION
      HEREDOC_REDIRECTION
      APPEND_REDIRECTION
      DELIMITER
      UNKNOWN
**Note:** The 'Unknown' token type is reserved for future purposes.
### Examples
    Input:  echo               a
    Tokens: UNQUOTED_WORD  DELIMITER  UNQUOTED_WORD
                echo        <spaces>       a

    Input:  echo\ a
    Tokens: UNQUOTED_WORD
              echo a

    Input:  'echo' "a"
    Tokens: SINGLE_QUOTED_WORD  DELIMITER  DOUBLE_QUOTED_WORD
                 echo            <space>             a

    Input:  e'c'"ho" a
    Tokens: UNQUOTED_WORD  SINGLE_QUOTED_WORD  DOUBLE_QUOTED_WORD  DELIMITER  UNQUOTED_WORD
                e                   c                 ho             <space>       a

    Input:  echo < a
    Tokens: UNQUOTED_WORD  DELIMITER  INPUT_REDIRECTION  DELIMITER  UNQUOTED_WORD
                echo        <space>            <          <space>         a        

    Input:  echo << a
    Tokens: UNQUOTED_WORD  DELIMITER  HEREDOC_REDIRECTION  DELIMITER  UNQUOTED_WORD
                echo        <space>            <          <space>         a        

    Input:  echo > a
    Tokens: UNQUOTED_WORD  DELIMITER  OUTPUT_REDIRECTION  DELIMITER  UNQUOTED_WORD
                echo        <space>            <          <space>         a        

    Input:  echo >> a
    Tokens: UNQUOTED_WORD  DELIMITER  APPEND_REDIRECTION  DELIMITER  UNQUOTED_WORD
                echo        <space>            <          <space>         a    

    Input:  ls | cat
    Tokens: UNQUOTED_WORD  DELIMITER  PIPE  DELIMITER  UNQUOTED_WORD
                 ls         <space>    |     <space>        a            

## Implementation

### LEXER

▶︎ Its task is to decompose the commands entered by the user.

▶︎ It parses the input into symbols and tokens.

▶︎ For example, it takes the command "ls -l" and converts it into a delimited array like [ "ls", "-l" ].


### PARSER 

▶︎ Parses symbols and tokens from the lexer to understand the structure of commands.

▶︎ Creates the syntax tree. This tree represents the structure of the command in a hierarchical way.

▶︎ For example, it converts the command "ls -l" into a tree structure.


### EXPANDER

▶︎ Evaluates variables, wildcards and other special characters within the command.

▶︎ For example, it replaces "~" with home directory or matches "*" with file names.


### EXECUTE

▶︎ Starts a real process using a tree structure.

▶︎ Creates a new process using system calls such as fork and exec and executes the command specified in that process.

▶︎ Returns the result to the user.

### BUILTINS
  
 **exit**
+ exits the shell with the status in the argument or the current status if none is specified
+ also needs a numeric argument for the status otherwise it will error
  
 **cd**
+ changes the current directory to the first argument provided
+ can be relative or absolute path
+ -- changes to HOME
+ - changes to OLDPWD
+ PWD and OLDPWD are set accordingly

**export**
+ with an argument it needs a valid identifier followed by an optional = and value
+ creates or changes the value of an existing environment variable
+ if no argument is provided it will print the environment variables in a weird format
 
**unset**
+ with a valid identifier as argument it unsets/deletes the environment variable
+ otherwise it shows an error

**pwd**
+ prints the current working directory to the stdout
  
**echo**

+ writes all the arguments to stdout followed by a newline
+ if the option -n is specified, no newline is added afterwards
+ some interesting differences are between "echo" in just lowercase and any other case version, as the latter would also accept multiple -n with as many "n" as we want

**env**
+ prints the current environment variables to the stdout


### Signals

+ during the entire parent process ctrl-\ is ignored

+ ctrl-C will always set a global variable to true, which quits the current processing and returns to readline

+ during readline ctrl-C needs some more functions so that we get a new line because readline doesn't return

+ the heredoc also has a special handler for readline

+ ctrl-\ isn't handled but it should inside heredocs which is an oversight on our part


## Useful shell utilities :


<img width="884" alt="Ekran Resmi 2023-12-24 02 00 35" src="https://github.com/facetint/minishell/assets/99668549/96413fde-0f58-4353-a8bf-ad7c6ef93644">


## Shell subset :


<img width="1149" alt="Ekran Resmi 2023-12-24 02 02 24" src="https://github.com/facetint/minishell/assets/99668549/3c889fb0-2727-4dca-bd88-d889304053ce">



## Shell features :


<img width="1149" alt="Ekran Resmi 2023-12-24 02 03 18" src="https://github.com/facetint/minishell/assets/99668549/96539ad5-74b5-43d8-8f1b-0bd95c8fb441">


## PIPE


In Bash, pipes are a fundamental mechanism for connecting the output of one command to the input of another command. This allows you to chain multiple commands together to perform more complex operations.

The basic syntax for a pipe operation is:

``` 
command1 | command2
```

This command sequence takes the output of command1 and feeds it directly into the input of command2. The output of command1 is processed by command2, and the result is displayed to the user or redirected for further processing.


EXAMPLE : 

**command : ls -l | grep "txt" | sort | nl**

<img width="1225" alt="Ekran Resmi 2023-12-24 14 38 56" src="https://github.com/facetint/minishell/assets/99668549/2b0c9e5a-ca26-48b3-95de-bb416d03c85b">

## Test Cases

### Common
```bash
cat | ls -l | wc -l
exit 21 42
exit | exit
exit -42
exit 42a
exit " -42"
cat file | cat << file
cat << file | cat << file
exit 256
echo facetint | cat << a << b << e
```
### Edge

```bash
ls | >> a < a > a << a cat
```
Should write heredoc input to file a.

```bash
export VAR=VAL
export VAR
env | grep VAR
```
The value of `VAR` should be `VAL`.

```bash
echo $0
```
Should print the first argument of your program. (eg: ./minishell)

```bash
env | grep SHLVL
```
This variable should be increased by 1 at init. If the inherited value is bigger than 999 bash sets it to 1 with a warning.

```bash
cd -
```
Should go old directory.

### Extreme
You don't have to implement these features.
```bash
'
```
Should wait for `'` char like heredoc.

```bash
export test1="o a"
ech$test1

export test2="'"
echo $test2
```
Should print `a` and `'` in order.

```bash
ls missingfile > error.txt 2>&1
```
Should write `ls: missingfile: No such file or directory` to error.txt

```bash
echo ~0
echo ~+
echo ~
```
Should print current directory.

```bash
echo ~-
```
Should print old directory.

```bash
cat < <(echo a)
```
Should print `a`.

```bash
export TEST_VAR=abc
echo ${TEST_VAR/a/b}
```
Should print `bbc`.

```bash
!-2
```
Should execute the last 2. executed command.



## Installation

### Clone the repository:
``` 
git clone https://github.com/facetint/minishell.git
cd minishell
make
```

### Run Minishell
```
./minishell
```










