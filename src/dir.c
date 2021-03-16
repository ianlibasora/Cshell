
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
#include <dirent.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"

#define MAXPATH 200

// dir command, list contents of directory

int dir(int lgt, char** lst, char* outFile, int out, bool detached, int* killPID) {
   // Determine paths to directories
   char path[MAXPATH];
   if (lgt == 1) {
      strcpy(path, ".");
   } else if (!strcmp(lst[1], "&") || !strcmp(lst[1], "<") || !strcmp(lst[1], ">") || !strcmp(lst[1], ">>")) {
      strcpy(path, ".");
   } else {
      strcpy(path, lst[1]);
   }

   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // Ternary operator: Run either stdout or redirection
      int ret = (out == 0 ? ls(path): lsRedirected(path, outFile, out)); 
      if (ret) {
         // If error raised
         exit(2);
      }
      exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}

int ls(char* path) {
   // ---------- REFERENCE BLOCK ---------
   // Based on source material from: https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
   // With minor style modifications to line(s) 70, 71, 75

   DIR *dPtr = opendir(path);
   struct dirent *dir;
   if (dPtr) {
      while ((dir = readdir(dPtr)) != NULL) {
         printf("%s\n", dir->d_name);
      }

   } else {
      fprintf(stderr, "Error. Could not open directory %s\n", path);
      return 1;
   }
   closedir(dPtr);
   // ---------- CLOSE BLOCK ----------

   return 0;
}

int lsRedirected(char* path, char* outFile, int out) {
   // Ternary operator: chooses between `w` or `a`
   FILE* fPtr = fopen(outFile, (out == 1 ? "w": "a"));
   
   if (fPtr != NULL) {
      // ---------- REFERENCE BLOCK ---------
      // Based on source material from: https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
      // With minor style modifications to line(s) 96, 97, 101
   
      DIR *dPtr = opendir(path);
      struct dirent *dir;
      if (dPtr) {
         while ((dir = readdir(dPtr)) != NULL) {
            fprintf(fPtr, "%s\n", dir->d_name);
         }

      } else {
         fprintf(stderr, "Error. cound not open directory %s\n", path);
         return 1;
      }
      closedir(dPtr);
      // ---------- CLOSE BLOCK ----------
   } else {
      fprintf(stderr, "Error. Error occured accessing %s\n", outFile);
      return 1;
   }
   fclose(fPtr);
   return 0;
}
