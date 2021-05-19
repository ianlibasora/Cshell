
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"
#include "cmd.h"

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

      if (cmd->out == 0) {
         // Run no redirection
         int i = 1;
         while (i < cmd->lgt && strcmp(cmd->args[i], "&")) {
            printf("%s ", cmd->args[i]);
            ++i;
         }
         printf("\n");
      } else {
         // Run redirection
         if (echoRedirect(cmd->lgt, cmd->args, cmd->outFile, cmd->out)) {
            // If error raised
            _exit(2);
         }
      }
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
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
