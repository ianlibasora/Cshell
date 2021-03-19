
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"

// Myshell batch mode runner function

int batchRunner(char* fName) {
   FILE* fPtr = fopen(fName, "r");
         
   if (fPtr == NULL) {
      fprintf(stderr, "Error. Error occured accessing %s\n", fName);
      return 1;
   }
   if (dup2(fileno(fPtr), 0) == -1) {
      fprintf(stderr, "Error. Error occured accessing %s\n", fName);
      return 1;
   }
   fclose(fPtr);
   return 0;
}
