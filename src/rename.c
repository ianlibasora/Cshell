
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"

// rename command

int chName(CMD* cmd, pid_t* killPID) {
   if (cmd->detached && cmd->lgt != 4 || !cmd->detached && cmd->lgt != 3) {
      fprintf(stderr, "Error. Invalid arguments for rename\n");
      return 1;
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

      // Rename arg[1] to arg[2]
      if (rename(cmd->args[1], cmd->args[2]) != 0) {
         fprintf(stderr, "Error. Unable to rename %s to %s\n", cmd->args[1], cmd->args[2]);
         _exit(1);
      }
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(2);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}
