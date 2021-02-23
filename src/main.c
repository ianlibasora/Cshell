
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"//Shell operation functions
#include "commands.h"//Shell commands
#include "enviroments.h"//Enviroment variable manipulation functions
#include "redirects.h"//Shell redirection functions

#define MAXARGS 100
#define MAXPATH 200

int main(int argc, char* argv[]) {
   if (argc == 2) {
      // If argv supplied, run in batch mode
      batchRunner(argv[1]);
      return 0;
   }

   extern char** environ;// Environment variables
   setExePath();//Assign the absolute path to the shell executable

   char* inp;// Input string pointer
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc;// Length of `inpArgs`
   char inFile[MAXPATH];
   char outFile[MAXPATH];

   bool detached = false;//Bools to state shell
   bool in = false;
   int out = 0;//0: no redirection, 1: tructation, 2: append
   bool* inPtr = &in;
   int* outPtr = &out;

   bool run = true;
   while (run) {
      cleanChildren();//Clean any present zombie processes
      inp = promptInput();// Full complete string of user input
      if (strlen(inp) <= 1) {
         // skip and continue loop if empty string
         continue;
      }

      inpArgc = splitString(inp, inpArgs, MAXARGS);
      if (!strcmp(inpArgs[inpArgc - 1], "&")) {
         detached = true;
      }
      if (checkRedirection(inpArgc, inpArgs, inPtr, outPtr) != 0) {
         detached = in = out = 0;
         clearArgs(inpArgc, inpArgs);
         continue;
      }
      getRedirectionFile(inpArgc, inpArgs, inFile, outFile, detached);

      if (!strcmp(inpArgs[0], "quit")) {
         run = false;
      } else if (!strcmp(inpArgs[0], "cd")) {
         cd(inpArgc, inpArgs, detached);
      } else if (!strcmp(inpArgs[0], "clr")) {
         system("clear");
      } else if (!strcmp(inpArgs[0], "dir")) {
         dir(inpArgc, inpArgs, out, detached);
      } else if (!strcmp(inpArgs[0], "echo")) {
         echo(inpArgc, inpArgs, detached);
      } else if (!strcmp(inpArgs[0], "environ")) {
         listENV(inpArgc, inpArgs, environ, detached);
      } else if (!strcmp(inpArgs[0], "pause")) {
         pauseShell();
      } else {
         fallbackChild(inpArgs);
      }

      detached = in = out = 0;
      clearArgs(inpArgc, inpArgs);
      cleanRedirectFiles(inFile, outFile);
   }

   printf("Quitting myshell\n");
   return 0;
}
