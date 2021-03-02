
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

#include "functions.h"
#include "commands.h"
#include "enviroments.h"
#include "redirects.h"

#define MAXARGS 100
#define MAXPATH 250
#define MAXLINE 500

// Myshell batch mode runner function

int batchRunner(char* fName) {
   char cwd[MAXPATH];
   getcwd(cwd, MAXPATH);
   setenv("PWD", cwd, 1);//Ensure that cwd is initialised properly
   extern char** environ;// Environment variables
   setExePath();//Assign the absolute path to the shell executable

   // Shell input handling
   char inp[MAXLINE];// Input string pointer
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc;// Length of `inpArgs`
   char inFile[MAXPATH];
   char outFile[MAXPATH];

   // Shell redirection/detach handling
   bool detached = false;//Bools to state shell
   bool in = false;
   int out = 0;//0: no redirection, 1: tructation, 2: append

   FILE* fPtr = fopen(fName, "r");
   if (fPtr != NULL) {
      fgets(inp, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         inpArgc = splitString(inp, inpArgs, MAXARGS);
         if (!strcmp(inpArgs[inpArgc - 1], "&")) {
            detached = true;
         }

         // If the redirection handling fails, reset and restart the loop
         if (checkRedirection(inpArgc, inpArgs, &in, &out) != 0 || getRedirectionFile(inpArgc, inpArgs, inFile, outFile, detached) != 0) {
            detached = in = out = 0;
            clearArgs(inpArgc, inpArgs);
            cleanRedirectFiles(inFile, outFile);
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
            listENV(environ, outFile, out, detached);
         } else if (!strcmp(inpArgs[0], "pause")) {
            pauseShell();
         } else if (!strcmp(inpArgs[0], "help")) {
            help(outFile, out, detached);
         } else {
            fallbackChild(inpArgs);
         }

         detached = in = out = 0;
         clearArgs(inpArgc, inpArgs);
         cleanRedirectFiles(inFile, outFile);
         fgets(inp, MAXLINE, fPtr);
      }

   } else {
      printf("Error. Error accessing %s\n", fName);
      fclose(fPtr);
      exit(1);
   }
   fclose(fPtr);
   exit(0);
}
