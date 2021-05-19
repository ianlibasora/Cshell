
#include <stdbool.h>

// Headerfile for CMD structure

#ifndef CMD_H
#define CMD_H

#define CMDMAXARGS 100
#define CMDMAXPATH 250

typedef struct CMD {
   int lgt;
   char* args[CMDMAXARGS];
   bool in;
   char inFile[CMDMAXPATH];
   int out;
   char outFile[CMDMAXPATH];
   bool detached;
} CMD;

int parseCMD(char* inp, CMD* cmd);
void cleanCMD(CMD* cmd, pid_t* killPID);
void checkDetached(CMD* cmd);

#endif
