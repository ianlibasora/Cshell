
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"
#include "cmd.h"

#define MAXPATH 250

// Help command

int help(CMD* cmd, pid_t* killPID) {
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (cmd->detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // Ternary operator: choose STDOUT/redirection operation
      int ret = (cmd->out == 0 ? promptHelp(): helpRedirect(cmd->outFile, cmd->out));
      if (ret) {
         // If error raised
         _exit(2);
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

int promptHelp() {
   char* helpFile = calloc(MAXPATH, sizeof(char));
   getHelpPath(helpFile);
   char* cmd[] = {"more", helpFile, NULL};
   execvp(cmd[0], cmd);

   free(helpFile);
   return 0;
}

int helpRedirect(char* outFile, int out) {
   char* helpFile = calloc(MAXPATH, sizeof(char));
   getHelpPath(helpFile);

   // Ternary operator: chooses between `w` or `a`
   FILE* outFilePtr = fopen(outFile, (out == 1 ? "w": "a"));

   if (outFilePtr != NULL) {
      FILE* manFilePtr = fopen(helpFile, "r");

      if (manFilePtr != NULL) {
         char c = fgetc(manFilePtr);
         while (!feof(manFilePtr)) {
            fprintf(outFilePtr, "%c", c);
            c = fgetc(manFilePtr);
         }

      } else {
         fprintf(stderr, "Error. Error accessing helpfile\n");
         return 1;
      }
      fclose(manFilePtr);
   } else {
      fprintf(stderr, "Error. Error accessing %s\n", outFile);
      return 1;
   }
   free(helpFile);
   fclose(outFilePtr);
   return 0;
}

void getHelpPath(char* fName) {
   char relativePath[] = "/manual/manual.md";
   char* path = strdup(getenv("SHELL"));
   path = realloc(path, (strlen(path) + 20) * sizeof(char));

   // Transform path to exe, to path to help readme.md file
   int i = strlen(path) - 1;
   int count = 0;
   while (0 <= i && count < 2) {
      // Go back 1 directory
      if (path[i] == '/') {
         ++count;
      }
      path[i] = '\0';
      --i;
   }
   strcat(path, relativePath);// Append relative path to full path
   strcpy(fName, path);
   // Note: memory allocated for `path` is freed by the caller
}
