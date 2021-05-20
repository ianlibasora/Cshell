
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
#include "cmd.h"
#include "redirects.h"

// Default fallback system call function when command is unknown

int fallback(CMD* cmd, pid_t* killPID) {
   // Fork and execute non internal program detached

   if (checkInterpreter(cmd->lgt, cmd->args[0], cmd->detached)) {
      // If external command is to open an interpreter
      // Disable the custom signal handler
      // Signal handler gets restarted when the shell returns back to the prompt loop

      if (cmd->detached) {
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

      if (cmd->detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // rm redirection/detachment related args
      // Can assume that handler has checked for invalid argument sequence
      char* newCmd[cmd->lgt];
      int j = 0;// newCmd index
      // i = lst index
      for (int i=0; i < cmd->lgt; ++i) {
         if (!strcmp(cmd->args[i], "<") || !strcmp(cmd->args[i], ">") || !strcmp(cmd->args[i], ">>")) {
            ++i;
            continue;
         } else if (!strcmp(cmd->args[i], "&")) {
            continue;
         }
         newCmd[j] = calloc(strlen(cmd->args[i]), sizeof(char));
         strcpy(newCmd[j], cmd->args[i]);
         ++j;
      }
      // Set last index of newCmd to NULL
      newCmd[j] = NULL;

      // Handle redirection
      if (redirect(cmd) != 0) {
         _exit(1);
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
