
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
#include <sys/ioctl.h>

#include "enviroments.h"

#define MAXPATH 250

// Environment variable manipulation / system functions

void setShellENV(char* key, char* value) {
   // Generic set key/value pair
   setenv(key, value, 1);
}

void setShellPath(char* key) {
   // Set cwd path for a given key
   static char path[MAXPATH];
   getcwd(path, MAXPATH);
   setenv(key, path, 1);
}

void setExePath() {
   // Set absolute path to shell executable
   
   // ------------ REFERENCE -------------

   static char path[MAXPATH];
   size_t lgt = readlink("/proc/self/exe", path, sizeof(path) - 1);
   if (lgt != -1) {
      path[lgt] = '\0';
      setenv("SHELL", path, 1);
   }
   // ------ END BLOCK -----
}

void getTermSize(short unsigned int* row, short unsigned int* col) {
   // ------ REF BLOCK ----
   struct winsize termSize;
   ioctl(0, TIOCGWINSZ, &termSize);
   *col = termSize.ws_col;
   *row = termSize.ws_row;
   // ------ END BLOCK --------
}

void getHelpPath(char* fName) {
   char relativePath[] = "/manual/readme.md";
   char* path = strdup(getenv("SHELL"));
   path = realloc(path, (strlen(path) + 5) * sizeof(char));
   
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
}
