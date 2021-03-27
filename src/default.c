
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "commands.h"
#include "enviroments.h"
#include "functions.h"
#include "sigFunctions.h"

// Default fallback system call function when command is unknown

int fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out, bool detached, int* killPID) {
   // Fork and execute non internal program detached

   if (checkInterpreter(lgt, lst[0], detached)) {
      // If external command is to open an interpreter
      // Disable the custom signal handler
      // Signal handler gets restarted when the shell returns back to the prompt loop

      if (detached) {
         // Stop the user if interpreter is being run detached
         fprintf(stderr, "Warning. Cannot run an interpreter detached.\n");
         return 1;
      }
      Signal(SIGINT, disabledHandler);
   }

   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

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

      if (in) {
         // If stdin redirection active
         FILE* stdinFile = fopen(inFile, "r");

         if (stdinFile == NULL) {
            fprintf(stderr, "Error. Error occured accessing %s\n", inFile);
            _exit(2);
         }
         if (dup2(fileno(stdinFile), 0) == -1) {
            fprintf(stderr, "Error. Error occured accessing %s\n", inFile);
            _exit(2);
         }
         fclose(stdinFile);
      }

      if (out != 0) {
         // If stdout redirection active
         // Ternary operator choose between write/append
         FILE* stdoutFile = fopen(outFile, (out == 1 ? "w": "a"));

         if (stdoutFile == NULL) {
            fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
            _exit(2);
         }

         if (dup2(fileno(stdoutFile), 1) == -1) {
            fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
            _exit(2);
         }
         fclose(stdoutFile);
      }

      execvp(newCmd[0], newCmd);
      clearArgs(j, newCmd);
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}

bool checkInterpreter(int lgt, char* arg, bool detached) {
   // Check if external command is to open an interpreter
   char interP[4][10] = {
      "python",
      "python3",
      "ipython3",
      "node"
   };

   if (detached && lgt != 2 || !detached && lgt != 1) {
      // Allow cases of detachment to pass for now
      // Handle detachment issue later
      return false;
   }

   for (int i=0; i < 4; ++i) {
      if (!strcmp(interP[i], arg)) {
         return true;
      }
   }
   return false;
}
