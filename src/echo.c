
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"
#include "cmd.h"
#include "redirects.h"

// echo command

int echo(CMD* cmd, pid_t* killPID) {
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (cmd->detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // Handle redirection
      if (redirect(cmd) != 0) {
         _exit(2);
      }

      for (int i=1; i < cmd->lgt; ++i) {
         if (!strcmp(cmd->args[i], "<") || !strcmp(cmd->args[i], ">") || !strcmp(cmd->args[i], ">>")) {
            ++i;
            continue;
         } else if (!strcmp(cmd->args[i], "&")) {
            continue;
         }
         printf("%s ", cmd->args[i]);
      }
      printf("\n");
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}
