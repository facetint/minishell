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
  - [Heredoc](#heredoc)
  - [Redirection](#redirections)
  - [Example Commands](#example-commands)
  - [Pipe](#pipe)
- [Installation](#installation)

## Introduction
In a shell, the user can run programs and also direct input from a file and output from a file.
    Bash allows users to enter commands and give instructions to the operating system.

## What is Bash
<!--
![bash](https://github.com/facetint/minishell/assets/99668549/9482ef70-4411-4efb-a871-2403ab33af95)
-->

* Bash is the shell, or command language interpreter, for the GNU operating system.

At first sight, Bash appears to be a simple command/response system, where users enter commands and Bash returns the results after those commands are run. However, Bash is also a programming platform and users are enabled to write programs that accept input and produce output using shell commands in shell scripts.

## How does the Bash work?

### Prompt Display

Bash displays a "prompt" for the user to enter a command. Typically, this prompt contains the user name, computer name, and working directory. The user can enter commands under this prompt.

<img width="892" alt="Ekran Resmi 2023-12-18 23 33 41" src="https://github.com/facetint/minishell/assets/99668549/d5399419-a858-4802-b4d7-b8f33b25a196">

### Command Input
The user can enter commands under the prompt. These commands are used to perform system-related operations (file management, program execution, network operations, etc.)

### Command Interpreter
Bash interprets commands entered by the user. This means checking if the command is a defined program, processing the parameters if necessary, and executing the command.

### Command Execution
It passes the interpreted command to the operating system through system calls and the operating system executes the command. For example, the ls command, a file listing command, requests the operating system to list files.

### Output and Error Checking 
After the command is executed, Bash checks whether the command is completed successfully. If an error occurs, it displays error messages. It also reports the exit status of the command (0 if successful, or a different value if failed).

### History and Retrieval
It keeps a history of commands entered by the user and allows the user to access this history and undo previous commands. This is achieved with the arrow keys or the history command.

### Shell Scripts
Bash also allows users to create shell scripts that contain a sequence of commands. These scripts are used to automate specific tasks by stringing together sequential commands.

These basic steps of Bash provide a user-friendly command-line environment and come with a wide range of commands. Users can customize Bash and there is extensive documentation and community support.

## How does this Minishell work?
Essentially we breaks down the process into 4 steps:
  * `lexer` accepts the raw string input of the user and converts it to tokens. 
  * `expander` accepts a list of tokens and replaces placeholders with its values.
  * `parser` accepts a list of tokens and converts them to commands.
  * `executor` accepts a list of commands and runs them.

### State Machines
When we wrote this project, we were inspired by state machines.

#### Prototypes of states

```c
    typedef void *(*t_lexer_state)(t_token **lexer_data, char *input, int *const i);
    /* a function pointer that returns void* and accepts 3 parameters. */

    typedef void *(*t_parser_state)(t_token **lexer_data, t_command *command);
    /* a function pointer that returns void* and accepts 2 parameters. */
```

The basic building blocks of a state machine are states and transitions. A state is a situation of a system depending on previous inputs and causes a reaction on following inputs. One state is marked as the initial state; this is where the execution of the machine starts. A state transition defines for which input a state is changed from one to another. Depending on the state machine type, states and/or transitions produce outputs.


![state-machine-example](https://github.com/facetint/minishell/assets/99668549/a5263d1a-815e-4f7c-a977-2298fb066e2c)

### Lexing

This minishell project uses 10 different types of tokens. The crucial point is understanding definitions of redirections and words.

**Words**: Words are minimal string parts of the user input. Words can be fit in quotes or not. Words can be contiguous with another word.
* `echo` has one word.
* `ec"ho"` has two words.
* `e'c'h"o"` has four words.

**Redirections:** Redirections are all unquoted `>`,`>>`,`<<` and `<` characters. That's all.

```c
typedef enum e_token_type {
      DOUBLE_QUOTED_WORD, SINGLE_QUOTED_WORD, UNQUOTED_WORD, PIPE, OUTPUT_REDIRECTION, INPUT_REDIRECTION, HEREDOC_REDIRECTION, APPEND_REDIRECTION, DELIMITER, UNKNOWN
} t_token_type;
```
**Note:** The 'Unknown' token type is reserved for future purposes.

```c
typedef struct s_token
{
	char		*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;
```

#### Examples
Here are some example user inputs and lexer outputs.

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

### Parsing 
* Parses symbols and tokens from the lexer to understand the structure of commands.
* Creates the syntax tree. This tree represents the structure of the command in a hierarchical way.
* For example, it converts the command "ls -l" into a tree structure.

```c
typedef struct s_redirection
{
	char		*redirected;
	int		redir_fd;
	int		flags;
}	t_redirection;


```

```c
typedef struct s_command
{
	char				**args;
	int				output;
	int				input;
	int				pid;
	t_redirection			*redirections;
	struct s_command		*next;
	struct s_command		*prev;
}	t_command;

```

### Expansion
* Evaluate variables and replace them with their values before running the command.
* For example, it replaces `$HOME` with the home directory.
* Also `$?` expression expands as the exit status of the last executed command.

### Execution
* Creates a new process using system calls such as fork and exec and executes the command specified in that process.
* Returns the result to the user.

### Builtin Commands

| Command | Description |
|---|---|
|`cd`| changes the current directory to the first argument provided. <br> can be relative or absolute path. <br> changes to HOME. <br> changes to OLDPWD. <br> PWD and OLDPWD are set accordingly |
|`echo`| Displays a line of text<br>Optional flag `-n`: do not output the trailing newline|
|`env` | Displays the environment variables|
|`exit`| exits the shell with the status in the argument or the current status if none is specified .<br>also needs a numeric argument for the status otherwise it will error |
|`export`|  with an argument it needs a valid identifier followed by an optional = and value. <br> creates or changes the value of an existing environment variable. <br> if no argument is provided it will print the environment variables in a weird format.|
|`pwd`| Shows the current directory as an absolute path.|
|`unset`|with a valid identifier as argument it unsets/deletes the environment variable. <br>otherwise it shows an error.|
 

### Signal Handling
* All `ctrl-\` signals are ignored for minishell.
* `ctrl-C` will always set a global variable to true, which quits the current processing and returns to readline
* during readline ctrl-C needs some more functions so that we get a new line because readline doesn't return
* the heredoc also has a special handler for readline
* ctrl-\ isn't handled but it should inside heredocs which is an oversight on our part

### Heredoc
In Bash, a "heredoc" (here document) is a construct used to feed a block of text or a series of commands into a specific process. Heredoc allows you to directly write text within a file or a script and pass this text as input to a command or operation.

```
command << eof
text
eof
```
Here, << eof denotes the beginning of the heredoc, and it is terminated with the label eof. The text or commands in between are taken until the line containing the specified label, and provided as input to the specified operation.

+ The usage of heredoc is commonly employed to make long and complex text blocks or command sequences more readable and manageable within text or script files.

### Redirections and Pipe

In Bash, redirections are used to redirect standard input and standard output, or standard error streams of a command. They are primarily used to perform operations such as writing the output of a command to a file, reading from a file, or redirecting the input/output from/to another command.

* Output Redirection(`>`): This operator redirects the output of a command to a specified file, overwriting the file if it already exists.
* Append Redirection(`>>`): This operator appends the output of a command to a specified file, preserving the existing content of the file.
* Input Redirection(`<`): This operator redirects the content of a file to the input of a command.
  * For example, in `cat < file`
    file is opened by the shell and assigned a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor).
    `cat`'s input is replaced as the file. So `cat` reads the file.
* Pipe(`|`): Redirects the output of command left to the input of command right.
  * For example, in `echo a | cat`
    `echo`'s output is replaced as the pipe by the shell.
    `cat`'s input is replaced with the same pipe. So they write and read to each other.

Programs does not know where to read or write. By default, every program writes to its STD_OUT(1) and reads from its STD_IN(0) but the shell changes files pointed by their STD_OUT and STD_IN.
 

### Useful shell utilities
<img width="884" alt="Ekran Resmi 2023-12-24 02 00 35" src="https://github.com/facetint/minishell/assets/99668549/96413fde-0f58-4353-a8bf-ad7c6ef93644">

### Shell subset
<img width="1149" alt="Ekran Resmi 2023-12-24 02 02 24" src="https://github.com/facetint/minishell/assets/99668549/3c889fb0-2727-4dca-bd88-d889304053ce">

### Shell features
<img width="1149" alt="Ekran Resmi 2023-12-24 02 03 18" src="https://github.com/facetint/minishell/assets/99668549/96539ad5-74b5-43d8-8f1b-0bd95c8fb441">

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
<img width="469" alt="Ekran Resmi 2024-04-04 ÖS 7 52 42" src="https://github.com/facetint/minishell/assets/99668549/8b51fcb4-27c0-4a48-99ef-adf03cbbacd3">

### Edge
Bash's edge case tests. We never say that minishells must have these implementations.

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

```bash
USER=abc
````
Sets User the variable to `abc`. (Use env and export commands for a surprise.)

```bash
'
```
Should wait for `'` char like heredoc.

```bash
export test="o '"
ech$test
```
Should print `'`.

<img width="469" alt="Ekran Resmi 2024-04-04 ÖS 7 53 48" src="https://github.com/facetint/minishell/assets/99668549/ef625091-f791-4dec-9fd8-48dbafaa34e4">


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
!-1
```
Should execute the last command.

```bash
export HISTSIZE=1000
````
Should set a limit to the history list.

```bash
echo $-
```
Shows bash's options. Idk how to implement it for minishell lol.

```bash
echo !$
```
Should print the last argument of the last executed command.

```bash
echo !!
```
It should expand the last executed command but it should expand the prompt.

```bash
/bin/ech? hello
/bin/ech[lower] hello
/bin/ech*o hello
```
Should print hello.

```bash
echo "\\n"
echo \\n
echo "\n"
echo \n
```
Should print `\n`, `\n`, `\n`, and `n`. (They are not newline.)

## Installation

1. Clone the repository: `git clone https://github.com/facetint/minishell.git`
2. run `cd minishell`
3. run `make`
4. run the executable: `./minishell`

### Testing
1. Install the [Criterion framework](https://github.com/Snaipe/Criterion?tab=readme-ov-file#packages).
2. run `make test`
