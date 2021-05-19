
#include <stdio.h>
#include <stdlib.h>
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

   // ------ REFERENCE BLOCK ------
   // Code snippet translated from: https://stackoverflow.com/a/5525712
   // Code translated from c++ to c

   static char path[MAXPATH];
   size_t lgt = readlink("/proc/self/exe", path, sizeof(path) - 1);
   if (lgt != -1) {
      path[lgt] = '\0';
      setenv("SHELL", path, 1);
   }
   // ------ END BLOCK ------
}
