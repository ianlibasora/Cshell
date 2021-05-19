
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"
#include "cmd.h"

// environ command, display all environment variables

int listENV(CMD* cmd) {
   if (cmd->detached) {
      // Detached
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));
         extern char** environ;// Exposes environment variables
         maskSIGINT();

         if (cmd->out == 0) {
            // Run no redirection
            for (int i=0; environ[i]; ++i) {
               printf("%s\n", environ[i]);
            }
         } else {
            // Run redirection
            if (listENVRedirect(environ, cmd->outFile, cmd->out)) {
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
   } else {
      // Non-Detached
      extern char** environ;// Exposes environment variables
      if (cmd->out == 0) {
         // Run no redirection
         for (int i=0; environ[i]; ++i) {
            printf("%s\n", environ[i]);
         }
      } else {
         // Run redirection
         if (listENVRedirect(environ, cmd->outFile, cmd->out)) {
            // If error raised
            return 2;
         }
      }
   }
   return 0;
}

int listENVRedirect(char** envs, char* outFile, int out) {
   // Ternary operator: chooses between `w` or `a`
   FILE* fPtr = fopen(outFile, (out == 1 ? "w": "a"));

   if (fPtr != NULL) {
      for (int i=0; envs[i]; ++i) {
         fprintf(fPtr, "%s\n", envs[i]);
      }
   } else {
      fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
      return 1;
   }
   fclose(fPtr);
   return 0;
}
