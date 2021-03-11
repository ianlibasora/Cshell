
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/wait.h>

#include "functions.h"// Shell operation functions
#include "commands.h"// Shell commands
#include "enviroments.h"// Enviroment variable manipulation functions
#include "redirects.h"// Shell redirection functions
#include "sigFunctions.h"// Signal handling functions

#define MAXARGS 100
#define MAXPATH 250

sigjmp_buf buf;

int main(int argc, char* argv[]) {
   if (argc > 1) {
      // If argv supplied, run in batch mode
      batchRunner(argv[1]);
      exit(0);
   }

   static char cwd[MAXPATH];
   getcwd(cwd, MAXPATH);
   setenv("PWD", cwd, 1);// Ensure that cwd is initialised properly
   setExePath();// Assign the absolute path to the shell executable

   // Shell input handling
   char* inp;// Input string pointer
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc = 0;// Length of `inpArgs`
   char inFile[MAXPATH];// Path of stdin redirection file
   char outFile[MAXPATH];// Path of stdout redirection file


   // Shell redirection/detach handling
   // Note: 
   // All commands, excluding `quit`, `cd`, `clear` run as children of the parent process
   // These are refered to as `Non-Always` and `Always` children commands
   // Detachment is determined by if the parent process should wait for the child process
   // cd however is still able to be run detached

   bool detached = false;// Bool to state shell detachment
   bool in = false;// Bool to state stdin redirection
   int out = 0;// 0: No redirection, 1: stdout tructation, 2: stdout append


   // Shell signal handling
   // When shell enters a command execution section, signal handling becomes active
   // If a SIGINT were to be raised, the signal handler will reset the loop, and kill the child process
   // Only used for commands `Always Children`
   // Note: will not kill detached processes due to the `active` flag being false

   bool active = false;// Bool to state if command execution in progress
   int killPID;// Pid of active process

   bool run = true;
   while (run) {
      // ---------- REFERENCE BLOCK ---------
      // Code snippet from: Randal E. Bryant, David R. O’Hallaron - Computer Systems. A Programmer’s Perspective [3rd ed.] (2016, Pearson)
      // Pg 811, fig 8.44
      // Code contains minor modifications to fit the purpose of a shell signal handler
      // Function source code located in `signalFunctions.c`

      if (!sigsetjmp(buf, 1)) {
         Signal(SIGINT, handler);
      } else {
         // If SIGINT triggers, cleanup shell before new prompt
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
         detached = in = out = inpArgc = 0;

         // Additional signal handling for (non-detached) child process SIGINT
         // Kills the unreapable process from SIGINT
         if (active) {
            kill(killPID, SIGTERM);
         }
         active = false;
      }
      // ---------- END BLOCK ---------

      cleanChildren();// Clean any present zombie processes
      inp = promptInput();// Prompts user for full complete string of user input
      if (checkInvalidString(inp)) {
         // Skip and restart loop if invalid string
         continue;
      }

      // Split string into array of args
      if (splitString(inp, &inpArgc, inpArgs, MAXARGS) != 0) {
         // Error handle invalid args
         clearArgs(inpArgc, inpArgs);
         detached = in = out = inpArgc = 0;
         continue;
      }
      detached = checkDetached(inpArgc, inpArgs);// Check if running detached

      // Checks and validates redirection and finds files associated with redirection
      if (checkRedirection(inpArgc, inpArgs, &in, &out) != 0 || getRedirectionFile(inpArgc, inpArgs, inFile, outFile, detached) != 0) {
         // If the redirection handling fails, reset and restart the loop
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
         detached = in = out = inpArgc = 0;
         continue;
      }


      // Non-Always children commands
      if (!strcmp(inpArgs[0], "quit")) {
         run = false;
      } else if (!strcmp(inpArgs[0], "cd")) {
         cd(inpArgc, inpArgs, detached);
         detached = false;// Ensure that cd & does not cause stoopage
      } else if (!strcmp(inpArgs[0], "clr")) {
         system("clear");
      } 
      

      // Always children commands
      active = true;
      if (!strcmp(inpArgs[0], "environ")) {
         listENV(outFile, out);
      } else if (!strcmp(inpArgs[0], "dir")) {
         dir(inpArgc, inpArgs, outFile, out, &killPID);
      } else if (!strcmp(inpArgs[0], "echo")) {
         echo(inpArgc, inpArgs, outFile, out, &killPID);
      } else if (!strcmp(inpArgs[0], "pause")) {
         pauseShell(&killPID);
      } else if (!strcmp(inpArgs[0], "help")) {
         help(outFile, out, &killPID);
      } else {
         fallbackChild(inpArgc, inpArgs, inFile, in, outFile, out, &killPID);
      }
      
      if (!detached) {
         // If not detached
         wait(NULL);
      }
      active = false;


      // Loop restart cleanup
      clearArgs(inpArgc, inpArgs);
      cleanRedirectFiles(inFile, outFile);
      detached = in = out = inpArgc = 0;
   }

   printf("Quitting myshell\n");
   exit(0);
}
