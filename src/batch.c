
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

#define MAXARGS 100
#define MAXPATH 200
#define MAXLINE 500

// Myshell batch mode runner function

int batchRunner(char* fName) {
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
   bool* inPtr = &in;
   int* outPtr = &out;

   FILE* fPtr = fopen(fName, "r");
   if (fPtr != NULL) {
      fgets(inp, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         printf("%s", inp);
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
