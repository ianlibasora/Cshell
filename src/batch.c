
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
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
