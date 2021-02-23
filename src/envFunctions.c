
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "enviroments.h"

#define MAXPATH 200

// Environment variable manipulation functions

void setShellENV(char* key, char* value) {
   // Generic set key/value pair
   setenv(key, value, 1);
}

void setShellPath(char* key) {
   // Set cwd path for a given key
   char path[MAXPATH];
   getcwd(path, MAXPATH);
   setenv(key, path, 1);
}

void setExePath() {
   // set absolute path to shell executable
   char path[MAXPATH];
   getcwd(path, MAXPATH);
   strcat(path, "/myshell");
   setenv("SHELL", path, 1);
}
