## Makefile and Compilation


### Overview
Written in the C programming language, the myshell project must be first compiled before it can be executed. To manage this, a number of makefiles are included with this project. Located throughout the project, the primary makefile resides in the `/bin` directory. All other makefiles as such, are simply just for ease of use, passing commands back to the primary makefile for execution. In total, there are 3 makefiles attached with this project, located in: 
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
   The `build` command is the default command which the makefile will execute when invoked. Tasked with compiling and linking all the necessary source files, it creates the executable for the myshell shell, and places it inside the `/bin` directory. As the default command, the user can also invoke this command through just invoking `make`. This shortcut executes the default command of a makefile.


- ### run
   The `run` command executes everything that the `build` command executes, with the addition that once compilation has finished, it will automatically start the myshell shell. 


- ### clean
   The `clean` command deletes the myshell executable, along with any compilation generated files.


## ***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
