
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"
#include "functions.h"

// Default fallback system call function when command is unknown

// -------  REFACTOR FOR ERROR HANDLING -------

void fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out) {
   // Fork and execute non internal program detached
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      
      if (in || out != 0) {
         // If stdin/stdout redirection active
         // Rm redirection related args
         // Can assume that redirection handler has checked for invalid redirection invokation
         char* newCmd[lgt];
         int i = 0;// lst index
         int j = 0;// newCmd index
         while (i < lgt) {
            if (!strcmp(lst[i], "<") || !strcmp(lst[i], ">") || !strcmp(lst[i], ">>")) {
               i += 2;
            } else {
               newCmd[j] = calloc(strlen(lst[i]), sizeof(char));
               strcpy(newCmd[j], lst[i]);
               ++i;
               ++j;
            }
         }
         // Set last index of newCmd to NULL
         newCmd[j] = NULL;

         if (in) {
            FILE* stdinFile = fopen(inFile, "r");
            dup2(fileno(stdinFile), 0);
            fclose(stdinFile);
         }
         if (out != 0) {
            FILE* stdoutFile = fopen(outFile, (out == 1 ? "w": "a"));
            // Ternary operator choose between write/append
            dup2(fileno(stdoutFile), 1);
            fclose(stdoutFile);
         }

         execvp(newCmd[0], newCmd);
         clearArgs(j, newCmd);
      } else {
         // Run normal no redirection
         execvp(lst[0], lst);
      }
      exit(0);
   } else if (pid == -1) {
      printf("Error. Fork error occured\n");
      exit(1);
   } else {
      // Parent does nothing, but should wait for execution to finished
      // Detached execution is offload to main shell
      wait(NULL);
   }
}
