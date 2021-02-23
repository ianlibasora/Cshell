
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

int dir(int lgt, char** lst, int out, bool detached) {
   // Determine paths to directories
   char path[MAXPATH];
   if (lgt == 1 || (lgt == 2 && detached)) {
      strcpy(path, ".");
   } else {
      strcpy(path, lst[1]);
   }

   // Determine redirection operation
   char outFile[MAXPATH];
   if (out != 0) {
      // Check enough args
      if (detached && lgt == 4) {
         strcpy(outFile, lst[2]);
      } else if (detached && lgt == 5) {
         strcpy(outFile, lst[3]);
      } else if (detached == false && lgt == 3) {
         strcpy(outFile, lst[2]);
      } else if (detached == false && lgt == 4) {
         strcpy(outFile, lst[3]);
      } else {
         printf("Error. Incorrect arguments for redirection\n");
         return 1;
      }
   }


   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         ls(path);
         exit(0);
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent, does nothing, operation pushed to background
   } else {
      ls(path);
   }
   return 0;
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

      closedir(dPtr);
   } else {
      printf("Error. cound not open directory %s\n", path);
   }
}
