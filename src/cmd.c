
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cmd.h"
#include "input.h"
#include "redirects.h"

// Functions for CMD structure handling

int parseCMD(char* inp, CMD* cmd) {
   if (checkInvalidString(inp)) {
      // If error, restart loop
      return 1;
   }
   if (splitString(inp, cmd) != 0 || checkRedirection(cmd) != 0 || getRedirectionFile(cmd) != 0) {
      // If error, restart loop
      return 2;
   }
   checkDetached(cmd);
   return 0;
}

void cleanCMD(CMD* cmd) {
   for (int i=0; i < cmd->lgt; ++i) {
      free(cmd->args[i]);
   }
   cmd->lgt = 0;
   cmd->in = false;
   strcpy(cmd->inFile, "");
   cmd->out = 0;
   strcpy(cmd->outFile, "");
   cmd->pid = 0;
}

void checkDetached(CMD* cmd) {
   for (int i=0; i < cmd->lgt; ++i) {
      if (!strcmp(cmd->args[i], "&")) {
         cmd->detached = true;
         return;
      }
   }
   cmd->detached = false;
}
