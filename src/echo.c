
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
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"

// echo command

int echo(int lgt, char** inp, char* outFile, int out, bool detached) {
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));

      if (out == 0) {
         // Run no redirection
         int i = 1;
         while (i < lgt && strcmp(inp[i], "&")) {
            printf("%s ", inp[i]);
            ++i;
         }
         printf("\n");
      } else {
         // Run redirection
         echoRedirect(lgt, inp, outFile, out);
      }
      exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(1);
   } else {
      // Parent
      if (!detached) {
         // If not running detached, wait
         wait(NULL);
      }
      return 0;
   }
}

int echoRedirect(int lgt, char** lst, char* outFile, int out) {
   // Ternary operator: chooses between `w` or `a` depending on value of `out`
   FILE* fPtr = fopen(outFile, (out == 1 ? "w": "a"));
   if (fPtr != NULL) {
      int i = 1;
      while (i < lgt && strcmp(lst[i], "&")) {
         // If redirection character encountered, skip 2 indexes
         // Note: can assume that `lst` has been checked that all redirection is valid
         if (!strcmp(lst[i], "<") || !strcmp(lst[i], ">") || !strcmp(lst[i], ">>")) {
            i += 2;
         } else {
            fprintf(fPtr, "%s ", lst[i]);
            ++i;
         }
      }
      fprintf(fPtr, "\n");
   } else {
      fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
      return 1;
   }
   fclose(fPtr);
   return 0;
}
