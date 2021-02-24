
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
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

// Myshell batch mode runner function

int batchRunner(char* fName) {
   extern char** environ;// Environment variables
   setExePath();//Assign the absolute path to the shell executable

   char* inp;// Input string pointer
   char* inpArgs[MAXARGS];// Array of strings (array of pointers)
   int inpArgc;// Length of `inpArgs`
   bool detached = false;//Bool to state if cmd to run detached

   printf("Batch mode running\n");
   
   return 0;
}
