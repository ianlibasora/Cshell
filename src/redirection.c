
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "redirects.h"
#include "cmd.h"

// Shell redirection/detach functions

int checkRedirection(CMD* cmd) {
   // Check args if redirection is required
   // Return 0 on sucess
   for (int i=0; i < cmd->lgt; ++i) {
      if (!strcmp(cmd->args[i], "<")) {
         if (cmd->in) {
            fprintf(stderr, "Error. Multiple use of \"<\" redirection\n");
            return 3;
         }
         cmd->in = true;
      } else if (!strcmp(cmd->args[i], ">")) {
         if (cmd->out != 0) {
            fprintf(stderr, "Error. Mixed use of \">\" and \">>\" redirection\n");
            return 1;
         }
         cmd->out = 1;
      } else if (!strcmp(cmd->args[i], ">>")) {
         if (cmd->out != 0) {
            fprintf(stderr, "Error. Mixed use of \">\" and \">>\" redirection\n");
            return 2;
         }
         cmd->out = 2;
      }
   }
   return 0;
}

int getRedirectionFile(CMD* cmd) {
   // Get the filenames for stdin/stdout redirection
   // Return 0 on sucess
   bool in, out;
   in = out = false;

   for (int i=0; i < cmd->lgt; ++i) {
      if (!in && !strcmp(cmd->args[i], "<")) {
         // If < detected
         // Check for correct arg
         if (i + 1 >= cmd->lgt || !strcmp(cmd->args[i + 1], "&") || !strcmp(cmd->args[i + 1], "<") || !strcmp(cmd->args[i + 1], ">") || !strcmp(cmd->args[i + 1], ">>")) {
            fprintf(stderr, "Error. Incorrect arguments for redirection\n");
            return 1;
         }
         strcpy(cmd->inFile, cmd->args[i + 1]);
         in = true;
      } else if (!out && (!strcmp(cmd->args[i], ">") || !strcmp(cmd->args[i], ">>"))) {
         // if > or >> detected
         // Check for correct args
         if (i + 1 >= cmd->lgt || !strcmp(cmd->args[i + 1], "&") || !strcmp(cmd->args[i + 1], "<") || !strcmp(cmd->args[i + 1], ">") || !strcmp(cmd->args[i + 1], ">>")) {
            fprintf(stderr, "Error. Incorrect arguments for redirection\n");
            return 2;
         }
         strcpy(cmd->outFile, cmd->args[i + 1]);
         out = true;
      }
   }
   return 0;
}

int redirect(CMD* cmd) {
   if (cmd->in) {
      // If STDIN redirection active
      FILE* stdinFile = fopen(cmd->inFile, "r");
      
      if (stdinFile == NULL) {
         fprintf(stderr, "Error. Error occured accessing %s\n", cmd->inFile);
         return 1;
      }
      
      if (dup2(fileno(stdinFile), 0) == -1) {
         fprintf(stderr, "Error. Error occured accessing %s\n", cmd->inFile);
         return 1;
      }
      fclose(stdinFile);
   }

   if (cmd->out != 0) {
      // If STDOUT redirection active
      // Ternary operator: choose truncate/append
      FILE* stdoutFile = fopen(cmd->outFile, (cmd->out == 1 ? "w": "a"));

      if (stdoutFile == NULL) {
         fprintf(stderr, "Error. Error occured accessing %s\n", cmd->outFile);
         return 2;
      }

      if (dup2(fileno(stdoutFile), 1) == -1) {
         fprintf(stderr, "Error. Error occured accessing %s\n", cmd->outFile);
         return 2;
      }
      
      fclose(stdoutFile);
   }
   return 0;
}
