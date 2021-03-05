
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

#include "functions.h"// Shell operation functions
#include "commands.h"// Shell commands
#include "enviroments.h"// Enviroment variable manipulation functions
#include "redirects.h"// Shell redirection functions
#include "sigFunctions.h"// Signal handling functions

#define MAXARGS 100
#define MAXPATH 250

// ----- ref os book
sigjmp_buf buf;
// ------ END BLOCK

int main(int argc, char* argv[]) {
   if (argc > 1) {
      // If argv supplied, run in batch mode
      batchRunner(argv[1]);
      exit(0);
   }

   static char cwd[MAXPATH];
   getcwd(cwd, MAXPATH);
   setenv("PWD", cwd, 1);// Ensure that cwd is initialised properly
   extern char** environ;// Expose environment variables
   setExePath();// Assign the absolute path to the shell executable

   // Shell input handling
   char* inp;// Input string pointer
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc = 0;// Length of `inpArgs`
   char inFile[MAXPATH];// Path of stdin redirection file
   char outFile[MAXPATH];// Path of stdout redirection file

   // Shell redirection/detach handling
   bool detached = false;// Bools to state shell detachment
   bool in = false;
   int out = 0;// 0: No redirection, 1: stdout tructation, 2: stdout append

   bool run = true;
   while (run) {
      // ----------- REF BLOCK FROM OS
      if (!sigsetjmp(buf, 1)) {
         Signal(SIGINT, handler);
      } else {
         // If SIGINT triggers, cleanup shell before new prompt
         detached = in = out = 0;
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
      }
      // ------- END BLOCK

      cleanChildren();// Clean any present zombie processes
      inp = promptInput();// Full complete string of user input
      if (strlen(inp) <= 1) {
         // Skip and restart loop if empty string
         continue;
      }
      inpArgc = splitString(inp, inpArgs, MAXARGS);// Split string into array of args
      detached = checkDetached(inpArgc, inpArgs);// Check if running detached

      // Checks and validates redirection and finds files associated with redirection
      // If the redirection handling fails, reset and restart the loop
      if (checkRedirection(inpArgc, inpArgs, &in, &out) != 0 || getRedirectionFile(inpArgc, inpArgs, inFile, outFile, detached) != 0) {
         detached = in = out = 0;
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
         continue;
      } 

      if (!strcmp(inpArgs[0], "quit")) {
         run = false;
      } else if (!strcmp(inpArgs[0], "cd")) {
         cd(inpArgc, inpArgs, detached);
      } else if (!strcmp(inpArgs[0], "clr")) {
         system("clear");
      } else if (!strcmp(inpArgs[0], "dir")) {
         dir(inpArgc, inpArgs, outFile, out, detached);
      } else if (!strcmp(inpArgs[0], "echo")) {
         echo(inpArgc, inpArgs, outFile, out, detached);
      } else if (!strcmp(inpArgs[0], "environ")) {
         listENV(environ, outFile, out, detached);
      } else if (!strcmp(inpArgs[0], "pause")) {
         pauseShell();
      } else if (!strcmp(inpArgs[0], "help")) {
         help(outFile, out, detached);
      } else {
         fallbackChild(inpArgc, inpArgs, inFile, in, outFile, out);
      }

      // Loop restart cleanup
      detached = in = out = 0;
      clearArgs(inpArgc, inpArgs);
      cleanRedirectFiles(inFile, outFile);
   }

   printf("Quitting myshell\n");
   exit(0);
}
