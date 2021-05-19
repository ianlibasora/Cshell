
#include <stdbool.h>

#define MAXARGS 100
#define MAXPATH 250

// Headerfile for CMD structure

#ifndef CMD_h
#define CMD_H

typedef struct {
   int lgt;
   char* args[MAXARGS];
   bool in;
   char inFile[MAXPATH];
   bool out;
   char outFile[MAXPATH];
   pid_t pid;
} CMD;

#endif
