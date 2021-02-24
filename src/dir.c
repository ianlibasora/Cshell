
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "commands.h"
#include "enviroments.h"

#define MAXPATH 200

// dir command, list contents of directory

void dir(int lgt, char** lst, char* outFile, int out, bool detached) {
   // Determine paths to directories
   char path[MAXPATH];
   if (lgt == 1) {
      strcpy(path, ".");
   } else if (!strcmp(lst[1], "&") || !strcmp(lst[1], "<") || !strcmp(lst[1], ">") || !strcmp(lst[1], ">>")) {
      strcpy(path, ".");
   } else {
      strcpy(path, lst[1]);
   }

   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         // Run either stdout or redirection
         out == 0 ? ls(path): lsRedirected(path, outFile, out); 
         exit(0);
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent, does nothing, operation pushed to background
   } else {
      // Normal non detached execution
      // Run either stdout or redirection
      out == 0 ? ls(path): lsRedirected(path, outFile, out);
   }
}

void ls(char* path) {
   // Based on source material from:
   // https://www.geeksforgeeks.org/c-program-list-files-sub-directories-directory/
   
   DIR *dPtr = opendir(path);
   struct dirent *dir;
   if (dPtr) {
      while ((dir = readdir(dPtr)) != NULL) {
         printf("%s\n", dir->d_name);
      }

   } else {
      printf("Error. cound not open directory %s\n", path);
   }
   closedir(dPtr);
}

void lsRedirected(char* path, char* outFile, int out) {
   char op[4];
   strcpy(op, (out == 1 ? "w": "a"));
   FILE* fPtr = fopen(outFile, op);
   
   if (fPtr != NULL) {
      // Based on source material from:
      // https://www.geeksforgeeks.org/c-program-list-files-sub-directories-directory/
   
      DIR *dPtr = opendir(path);
      struct dirent *dir;
      if (dPtr) {
         while ((dir = readdir(dPtr)) != NULL) {
            fprintf(fPtr, "%s\n", dir->d_name);
         }

      } else {
         printf("Error. cound not open directory %s\n", path);
      }
      closedir(dPtr);
   } else {
      printf("Error. Error occured accessing %s\n", outFile);
   }
   fclose(fPtr);
}
