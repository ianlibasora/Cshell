
#include <stdbool.h>
#include <sys/types.h>

// Headerfile for CMD structure

#ifndef CMD_H
#define CMD_H

#define CMDMAXARGS 5
#define CMDMAXPATH 250

typedef struct CMD {
   int lgt;
   char* args[CMDMAXARGS];
   bool in;
   char inFile[CMDMAXPATH];
   bool out;
   char outFile[CMDMAXPATH];
   pid_t pid;
} CMD;

int parseCMD(char* inp, CMD* cmd);

#endif
