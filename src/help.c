
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
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"

#define MAXLINE 500
#define MAXPATH 250

// Help command

int help(char* outFile, int out, bool detached) {
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));

      // Choose between either normal/redirection operation
      int ret = (out == 0 ? promptHelp(): helpRedirect(outFile, out));
      if (ret) {
         // If error raised
         exit(2);
      }
      exit(0);         
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(1);
   } else {
      // Parent
      if (!detached) {
         // If not running detached
         wait(NULL);
      }
   }
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
   char line[MAXLINE];
   char* helpFile = calloc(MAXPATH, sizeof(char));
   getHelpPath(helpFile);
   
   // Ternary operator: chooses between `w` or `a`
   FILE* outFilePtr = fopen(outFile, (out == 1 ? "w": "a"));

   if (outFilePtr != NULL) {
      FILE* manFilePtr = fopen(helpFile, "r");
      
      if (manFilePtr != NULL) {
         fgets(line, MAXLINE, manFilePtr);
         while (!feof(manFilePtr)) {
            fprintf(outFilePtr, "%s", line);
            fgets(line, MAXLINE, manFilePtr);
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
   char relativePath[] = "/manual/readme.md";
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
