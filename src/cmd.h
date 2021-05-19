
// Headerfile for CMD structure

#ifndef CMD_H
#define CMD_H

#define CMDMAXARGS 100
#define CMDMAXPATH 250

typedef struct CMD {
   int lgt;// Length of CMD args
   char* args[CMDMAXARGS];// CMD Array of strings (array of pointers)
   bool in;// Bool for STDIN redirection
   char inFile[CMDMAXPATH];// Path of STDIN redirection file
   int out;// Flag for STDOUT redirection. 0: No redirection, 1: STDOUT tructation, 2: STDOUT append
   char outFile[CMDMAXPATH];// Path of STDOUT redirection file
   bool detached;// Bool for shell detachment
} CMD;

int parseCMD(char* inp, CMD* cmd);
void cleanCMD(CMD* cmd, pid_t* killPID);
void checkDetached(CMD* cmd);

#endif
