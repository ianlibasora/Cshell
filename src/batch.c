
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

#include "functions.h"// Shell operation functions
#include "commands.h"// Shell commands
#include "enviroments.h"// Enviroment variable manipulation functions
#include "redirects.h"// Shell redirection functions

#define MAXARGS 100
#define MAXPATH 250
#define MAXLINE 500

// Myshell batch mode runner function

int batchRunner(char* fName) {
   static char cwd[MAXPATH];
   getcwd(cwd, MAXPATH);
   setenv("PWD", cwd, 1);// Ensure that cwd is initialised properly
   setExePath();// Assign the absolute path to the shell executable

   // Shell input handling
   char inp[MAXLINE];// Input string
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc = 0;// Length of `inpArgs`
   char inFile[MAXPATH];// Path of stdin redirection file
   char outFile[MAXPATH];// Path of stdout redirection file

   // Shell redirection/detach handling
   bool detached = false;// Bool to state shell detachment
   bool in = false;// Bool to state stdin redirection
   int out = 0;// 0: No redirection, 1: stdout tructation, 2: stdout append

   FILE* fPtr = fopen(fName, "r");
   if (fPtr != NULL) {
      while (fgets(inp, MAXLINE, fPtr) != NULL) {
         cleanChildren();// Clean any present zombie processes
         printf("Input: %s\n", inp);
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

         if (!strcmp(inpArgs[0], "cd")) {
            cd(inpArgc, inpArgs, detached);
         } else if (!strcmp(inpArgs[0], "clr")) {
            system("clear");
         } else if (!strcmp(inpArgs[0], "dir")) {
            dir(inpArgc, inpArgs, outFile, out, detached);
         } else if (!strcmp(inpArgs[0], "echo")) {
            echo(inpArgc, inpArgs, outFile, out, detached);
         } else if (!strcmp(inpArgs[0], "environ")) {
            listENV(outFile, out, detached);
         } else if (!strcmp(inpArgs[0], "pause")) {
            pauseShell();
         } else if (!strcmp(inpArgs[0], "help")) {
            help(outFile, out, detached);
         } else {
            fallbackChild(inpArgc, inpArgs, inFile, in, outFile, out, detached);
         }

         // Loop restart cleanup
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
         detached = in = out = inpArgc = 0;
      }

   } else {
      fprintf(stderr, "Error. Error accessing %s\n", fName);
      fclose(fPtr);
      exit(1);
   }
   fclose(fPtr);
   exit(0);
}
