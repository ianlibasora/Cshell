
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
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// echo command

void echo(int lgt, char** inp, char* outFile, int out, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         if (out == 0) {
            // Run no redirection
            for (int i=1; i < lgt-1; ++i) {
               printf("%s ", inp[i]);
            }
            printf("\n");
         } else {
            // Run redirection
            echoRedirect(lgt, inp, outFile, out);
         }
         exit(0);
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Normal non detached operation
      if (out == 0) {
         // Run no redirection
         for (int i=1; i < lgt; ++i) {
            printf("%s ", inp[i]);
         }
         printf("\n");
      } else {
         // Run redirection
         echoRedirect(lgt, inp, outFile, out);
      }
   }
}

void echoRedirect(int lgt, char** lst, char* outFile, int out) {
   char op[4];
   strcpy(op, (out == 1 ? "w": "a"));

   FILE* fPtr = fopen(outFile, op);
   if (fPtr != NULL) {
      int i = 1;
      while (strcmp(lst[i], ">") && strcmp(lst[i], ">>") && i < lgt) {
         fprintf(fPtr, "%s ", lst[i]);
         ++i;
      }
      fprintf(fPtr, "\n");
   } else {
      printf("Error. Error occured accessing %s\n", outFile);
   }
   fclose(fPtr);
}
