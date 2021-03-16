
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

#include "sigFunctions.h"
#include <signal.h>

#include "commands.h"
#include "enviroments.h"
#include "functions.h"

// Default fallback system call function when command is unknown

int fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out, int* killPID) {
   // Fork and execute non internal program detached
   
   if (lgt == 1 && checkInterpreter(lst[0])) {
      // If external command to to open an interpreter
      // Disable the custom signal handler
      // Signal handler gets restarted when the shell returns back to the prompt loop
      Signal(SIGINT, disabledHandler);
   }
   
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid(); 

      // Rm redirection/detachment related args
      // Can assume that handler has checked for invalid argument sequence  
      char* newCmd[lgt];
      int j = 0;// newCmd index
      // i = lst index
      for (int i=0; i < lgt; ++i) {
         if (!strcmp(lst[i], "<") || !strcmp(lst[i], ">") || !strcmp(lst[i], ">>")) {
            ++i;
            continue;
         } else if (!strcmp(lst[i], "&")) {
            continue;
         }
         newCmd[j] = calloc(strlen(lst[i]), sizeof(char));
         strcpy(newCmd[j], lst[i]);
         ++j;
      }
      // Set last index of newCmd to NULL
      newCmd[j] = NULL;
      
      if (in || out != 0) {
         // If stdin/stdout redirection active
         if (in) {
            FILE* stdinFile = fopen(inFile, "r");
            if (stdinFile == NULL) {
               fprintf(stderr, "Error. Error occured accessing %s\n", inFile);
               exit(2);
            }
            if (dup2(fileno(stdinFile), 0) == -1) {
               fprintf(stderr, "Error. Error occured accessing %s\n", inFile);
               exit(2);
            }
            fclose(stdinFile);
         }

         if (out != 0) {
            // Ternary operator choose between write/append
            FILE* stdoutFile = fopen(outFile, (out == 1 ? "w": "a"));
            if (stdoutFile == NULL) {
               fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
               exit(2);
            }

            if (dup2(fileno(stdoutFile), 1) == -1) {
               fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
               exit(2);
            }
            fclose(stdoutFile);
         }

      }

      execvp(newCmd[0], newCmd);
      clearArgs(j, newCmd);
      exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}

bool checkInterpreter(char* arg) {
   // Check if external command is to open an interpreter
   char interP[4][10] = {
      "python", 
      "python3", 
      "ipython3", 
      "node"
   };

   for (int i=0; i < 4; ++i) {
      if (!strcmp(interP[i], arg)) {
         return true;
      }
   }
   return false;
}
