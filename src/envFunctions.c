
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

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
