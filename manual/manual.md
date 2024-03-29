# Cshell User Usage Manual


## Description
Cshell is a command line interface  through which a user may interface with the computer operating system. Built using the C programming language, it allows the user to access and command operating system functions through human readable commands. Hosting a number of internally implemented system commands, cshell is sh-compatable with other sh-based shells such as `bash` and `zsh`. 


## Makefile and Compilation


### Overview
Written in the C programming language, the cshell project must be first compiled before it can be executed. To manage this, a number of makefiles are included with this project. Located throughout the project, the primary makefile resides in the `/bin` directory. All other makefiles as such, are simply just for ease of use, passing commands back to the primary makefile for execution. In total, there are 3 makefiles attached with this project, located in: 
- `/` project root
- `/bin` directory
- `/src` directory

Whenever the user wishes to use the makefiles, they should be located in one of these three directories. 


### Makefile options
To call the makefile to execute a certain operation, the user must type the prefix `make`, followed by the desired command into the command line, separated by a space. For example:
```
make build
```

The makefiles come with 3 commands which the user may invoke:

- ### build (default)
   The `build` command is the default command which the makefile will execute when invoked. Tasked with compiling and linking all the necessary source files, it creates the executable for the cshell shell, and places it inside the `/bin` directory. As the default command, the user can also invoke this command through just invoking `make`. This shortcut executes the default command of a makefile.


- ### run
   The `run` command executes everything that the `build` command executes, with the addition that once compilation has finished, it will automatically start the cshell shell. 


- ### clean
   The `clean` command deletes the cshell executable, along with any compilation generated files.


## Cshell Usage Guide


### Cshell Invocation
```
cshell [batchfile]
```

When invoked without suppling an argument, cshell will execute in prompt mode. Prompt mode is an interactive interface, through which the user may interact and invoke system commands.

When invoked with an argument, cshell will execute in batch mode. When it batch mode, cshell expects the supplied argument to be the filename to a batchfile. Cshell will read this file, and execute commands from this file. Once cshell has finished execution of all commands, cshell will close.


### Prompt Mode User Usage Guide
Once started, cshell will display a prompt and wait for user input into the shell. Key to giving the user situational awareness, the prompt also displays a number of variables to the user. Mirroring the `bash` shell prompt, the user’s username, host machine, and current working directory are displayed. The username simply refers to the user’s username, the host machine refers to the system name of the current machine, and the current working directory refers to the directory in which the user is currently located. This prompt follows the syntax: 

```
username@hostmachine:CurrentWorkingDirectory$
```

When a command is entered into the shell, the command is parsed and validated by cshell. Validation checks include IO redirection and background execution checks. 

For details, refer to *IO redirection*, *Background Execution* respectively. 

Following command validation, the command is first checked against the internally implemented commands of cshell. If it is an internal command, the subsequent internal command is executed. If the command invoked is not internally implemented by cshell, the command is passed to the parent shell for execution.  After command execution, the shell will once again prompt the user input. 

For details relating shell internal commands, refer to *Internal Commands.*

At any stage, the user may also raise a keyboard interrupt `(SIGINT)` to stop the current foreground command. Invoked by pressing `ctrl+c`, the shell will immediately stop and return to the user prompt. 

For details, refer to *Signal Handling.*


## Internal Commands

```
Key:
[arguments]: Optional arguments
<arguments>: Mandatory arguments
```

- ### `exit`
   Exits and closes cshell.

   Extra operations supported: None


- ### `cd [directory]`
   The `cd` command changes the current working directory of the shell. When invoked, the shell will attempt to change directory into `[directory]`. Upon completion of the `cd` command, the shell prompt and system `PWD` variable will update to reflect this change. If the supplied new directory is deemed invalid, an error is raised to the user. If no argument is supplied by the user, then `cd` will change directory into the user's home directory.

   Extra operations supported: Background Execution, SIGINT Handling
   
   For details, refer to *Background Execution*, *Signal Handling* respectively.


- ### `clr`
   The `clr` or clear command clears the shell command line. When invoked, the command line will be cleared, presenting the user with a clean command line and a new prompt.

   Extra operations supported: None


- ### `environ`
   The `environ` or environment command displays all the environment variables of the operating system, one per line. 

   For details regarding environment variables, refer to *Environments*. 
   
   When invoked with STDOUT redirection, the output of the command is redirected and output to the corresponding file.

   Extra operations supported: Background Execution, STDOUT Redirection, SIGINT Handling
   
   For details, refer to *Background Execution*, *IO Redirection*, *Signal Handling* respectively.


- ### `dir [directory]`
   The `dir` command displays the contents of `[directory]`. When invoked with a valid `[directory]`, the absolute contents of the directory will be displayed, one per line. This will include any hidden files or directories which have been marked with a preceding `"."`. If no `[directory]` is provided, then the contents of the current directory will be displayed. When invoked with STDOUT redirection, the output of the command is redirected and output to the corresponding file.

   Extra operations supported: Background Execution, STDOUT Redirection, SIGINT Handling

   For details, refer to *Background Execution*, *IO Redirection*, *Signal Handling* respectively.


- ### `echo [arguments]`
   The `echo` command displays `[arguments]` to the command line, single space character separated. When invoked with STDOUT redirection, the output of the command is redirected and output to the corresponding file.

   Extra operations supported: Background Execution, STDOUT Redirection, SIGINT Handling

   For details, refer to *Background Execution*, *IO Redirection*, *Signal Handling* respectively.


- ### `pause`
   The `pause` command pauses the shell until the `enter` key is again pressed by the user. All input and signals as such are ignored until the `enter` key is pressed.

   Extra operations supported: Background Execution

   For details, refer to *Background Execution*.


- ### `help`
   The `help` command displays the shell user manual. When invoked with STDOUT redirection, the output of the command is redirected and output to the corresponding file. When invoked without IO redirection, the `help` command returns an interactive help manual to the shell. This interactive prompt utilises the `more` filter. The following keys provide the basic controls for the `more` filter:
   - `enter`: View next line
   - `space`: View next page
   - `b`: View previous page
   - `q`: Quit

   For details with the `more` filter, refer to [[1]] in *References*

   Extra operations supported: Background Execution, STDOUT Redirection, SIGINT Handling

   For details, refer to *Background Execution*, *IO Redirection*, *Signal Handling* respectively.


- ### `rename <source> <destination>`
   The `rename` command renames the path specified by `<source>` into `<destination>`. The `<source>` and `<destination>` arguments are mandatory for this command. The `rename` command may be used to rename files and directories. Both `<source>` and `<destination>` arguments must be of same type, ie. a `<source>` of type `file` must be paired with a `<destination>` of type `file`.

   Extra operations supported: Background Execution, SIGINT Handling

   For details, refer to *Background Execution*, *Signal Handling* respectively.


## External Commands
Cshell allows for the execution of external commands. If a specific command is not listed within the *Internal Commands* section, then they are deemed external commands. Commands such as program execution are therefore supported by cshell. Full STDIN / STDOUT redirection is also supported with external commands. Note: Interpreters such as `python3` may not be invoked with background execution.

Extra operations supported: Background Execution, IO Redirection, SIGINT Handling

For details, refer to *Background Execution*, *IO Redirection*, *Signal Handling* respectively.


## IO Redirection

### Overview
Cshell supports both STDIN and STDOUT redirection for external commands and internal commands. Cshell supports 2 forms of STDOUT redirection, truncation and append. STDOUT truncation will output to a destination, overwriting any existing data. STDOUT append will output to a destination, but will append the data to any already existing data.

### Invocation
In cshell, STDIN redirection is invoked by the `<` character, followed by the input file, separated by a whitespace character.

Example:
```
./program.exe < input.txt
```


STDOUT truncation is invoked by the `>` character, followed by the output destination, separated by a whitespace character.

Example:
```
dir > a.txt
```


STDOUT append is invoked by the `>>` character, followed by the output destination, separated by a whitespace character.

Example:
```
dir >> a.txt
```

If IO redirection is invoked and does not match this syntax, an error is raised to the user and execution is cancelled.


### Implementation
Cshell implements STDIN and STDOUT redirection through pointers and the `dup2()` system call. For details, refer to [[2]], [[3]] in *References*.

## Environments
Environment variables are a set of dynamic variables, shared throughout a computer operating system. These global variables can be accessed by any program through interfacing with the operating system shell, and therefore may affect their execution. Example environment variables which are useful to programs may be the `PWD` variable, containing the value of the current directory, or more importantly the `PATH` variable, containing all the directories which are in the operating system path. This is important as an operating system’s path variable states the directories in which it will search for executables upon program invocation. As such, only programs located within the directories stated by the `PATH` variable can be executed.

As such, environment variables, paired with an operating system shell, may form the foundation for other subsequent programs within an operating system

For further details, refer to [[4]] in *References*.


## Processes
Within operating systems, processes are the concept of programs currently in active execution. While a process can be seen as a program, a program however cannot always be seen as a process. While a program may contain the specific instructions which a computer will need to execute, a program by itself cannot execute this code. Provided this environment by the operating system, once a program is loaded into memory and begins active execution, it becomes a process. With modern day operating systems today capable of handling multiple processes running concurrently, the idea of processes are key to the management and design of systems to support this capability. 

Creating an almost containerised environment from which programs can be executed, processes are composed of several sub-components. Once created, the process *text* section is tasked with holding a copy of the program code. In addition to this, the process also begins to define spaces for stack, heap and data storage. While the process *data* section is simply used for global program variables, *stack* and *heap* memory in particular are of key importance to the program. While having access to available memory is a requirement for a program to run, having distinct access to both stack and heap memory is a great memory management tool for programming languages like C. Used to store both small temporary data, or much larger long term data, such are critical for program execution. 

While a process allows for the execution of a program, it does not inherently have the ability to control execution. Instead, controlled by an accompanying Process Control Block (PCB) paired to a particular process, it is the PCB which controls the actions of a particular process. Also consisting of several important sub-components, the PCB contains information such as *registers*, *memory limits* and *opened files*. In particular to process control, using information such as the *program counter*, *process state*, and *registers*, the PCB, along with an operating system is able to control the execution of a process. While overall multiprocessor control is a task for an operating system scheduler, it is the responsibility of the PCB to control the direct actions of a process. This is in particular is the task of the PCB *program counter*, which points to the location of the next instruction which needs execution. 

In terms of overall process control, the operating system uses the PCB *process state* status to control process execution. Consisting of the *new*, *running*, *waiting*, *ready*, and *terminated* flags, they state the current status of a given process. Usually running in a *running*, *waiting*, *ready* cycle, this cycle both depicts and signals to the operating system if the process is ready for execution. In particular key to efficient process scheduling, among the goals of an operating system is to keep the CPU as busy as possible. Using the *process state* status flags, an operating system can efficiently schedule for processes to be executed in a matter which results in the least amount of downtime for a CPU. In the context of programs themselves, simple IO operations are common bottlenecks causing a CPU downtime. While to humans, computer memory and register speeds appear instantaneous, every nanosecond counts from the perspective of computers. Usually resolved by the *waiting* status flag, it ultimately signals the operating system to deallocate the assigned processor, allowing for other processes to be executed while the current process waits for IO to finish. Once IO has finished, only then will the process be pushed into the *ready* queue, waiting to be allocated a processor. While mostly resulting from IO blockages, the operating system itself can also interrupt a running process due to it exhausting its allocated time. This will similarly push the process to the *ready* queue. Simply due to the constantly in demand computer resources, processes are time limited with processors. 

For further details, refer to [[5]] in *References.*


## Background Execution

### Overview
Background execution refers to the execution of commands and programs in a background process, while the main process may continue to serve another user in the foreground. From the perspective of a user, this may come in the form of running a program in the background, while the user continues to interact with the shell in the foreground. Overall however, background execution is the basis of multiprocessing. Given the limited number of processors in a computer, a computer without the ability to handle multiprocessing would be very limited in the number of programs which it can simultaneously handle. Within the command line interface of cshell however, background execution is commonly used to run programs in the background, while the user continues to use and interact with the shell in the foreground. Outside of the command line interface, background execution may also come in the form of a user running multiple applications such as internet browsers concurrently.

For details with processes, refer to *Processes*


### Invocation 
Background execution may be invoked on a supporting command or program by the invocation of the `&` character. This character, placed at the end of the command or program, and signifies background execution for that particular command or program.

Example:
```
./program.exe argument1 &
```


### Implementation
Cshell utilises the `fork()` system call to manage background execution. 

For details, refer to [[6]] in *References.*


## Signal Handling

### Overview
When a user raises a keyboard interrupt `(SIGINT)` with `ctrl+c` in cshell, the `SIGINT` is handled by cshell’s custom signal handler. Within operating systems, signals are messages within the operating system which are passed between processes notifying some event occurring. Specifically with keyboard interrupts, it instructs the operating system to stop a specific process running. In cshell, keyboard interrupts can be used to stop a running foreground process. When a signal interrupt is raised with a running foreground process, the process is stopped, and the user is returned to the shell prompt. Keyboard interrupts do not affect processes running in the background. When a command line interpreter like `python3` is invoked in cshell, keyboard interrupts are passed into the called interpreter. 

For details regarding processes, refer to *Processes*

### Implementation
Cshell utilises code obtained from [7]. For details, refer to *References.*


## References

[[1]] Eric Shienbrood, UC Berkeley. Modified by Geoff Peck, UCB to add underlining, single spacing. Modified by John Foderaro, UCB to add -c and MORE environment variable. Michael Kerrisk, man7.org. [*Linux Programmer's Manual*][1]. Accessed: 17.03.2021 [Online]. Available: https://man7.org/linux/man-pages/man1/more.1.html

[[2]] Michael Kerrisk, man7.org. [*Linux Programmer's Manual*][2]. Accessed: 17.03.2021 [Online]. Available: https://man7.org/linux/man-pages/man2/dup.2.html

[[3]] gnu.org. [*Linux, 13.4 Descriptors and Streams manual*][3]. Accessed: 17.03.2021 [Online]. Available: https://www.gnu.org/software/libc/manual/html_node/Descriptors-and-Streams.html

[[4]] The Open Group. [*UNIX Specification, Environment Variables*][4]. Accessed: 17.03.2021 [Online]. Available: https://pubs.opengroup.org/onlinepubs/7908799/xbd/envvar.html

[[5]] Silberschatz, Galvin, and Gagne. *3.1 Process Concept* in [*Operating System Concepts, 8th Edition*][5], Hoboken, NJ, USA, Wiley, 2008, ch3.1. Available: https://learning.oreilly.com/library/view/Operating+System+Concepts,+8th+Edition/9780470128725/silb_9780470128725_oeb_c03_r1.html#h1

[[6]] Michael Kerrisk, man7.org. [*Linux Programmer's Manual*][6]. Accessed: 17.03.2021 [Online]. Available: https://man7.org/linux/man-pages/man2/fork.2.html

[7] Randal E. Bryant, David R. O’Hallaron. *Writing Signal Handlers* and *Nonlocal Jumps* in *Computer Systems. A Programmer’s Perspective [3rd ed.]*, London, UK, Pearson, 2016, ch8.5.5, p801, fig8.38, ch8.6, p811, fig 8.44 


[1]: <https://man7.org/linux/man-pages/man1/more.1.html>
[2]: <https://man7.org/linux/man-pages/man2/dup.2.html> 
[3]: <https://www.gnu.org/software/libc/manual/html_node/Descriptors-and-Streams.html>
[4]: <https://pubs.opengroup.org/onlinepubs/7908799/xbd/envvar.html>
[5]: <https://learning.oreilly.com/library/view/Operating+System+Concepts,+8th+Edition/9780470128725/silb_9780470128725_oeb_c03_r1.html#h1>
[6]: <https://man7.org/linux/man-pages/man2/fork.2.html>
