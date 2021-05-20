
#include <stdbool.h>

#include "cmd.h"

// Headerfile for shell command functions

#ifndef COMMANDS_H
#define COMMANDS_H

// cd
int cd(CMD* cmd);
void changeDir(char* path);

// echo
int echo(CMD* cmd, pid_t* killPID);

// environ
int listENV(CMD* cmd);
int listENVRedirect(char** envs, char* outFile, int out);

// dir
int dir(CMD* cmd, pid_t* killPID);
int ls(char* path);

// fallback execution
int fallback(CMD* cmd, pid_t* killPID);
bool checkInterpreter(int lgt, char* arg, bool detached);

// pause
int pauseShell(CMD* cmd, pid_t* killPID);

// help
int help(CMD* cmd, pid_t* killPID);
int promptHelp();
int helpRedirect(char* outFile, int out);
void getHelpPath(char* fName);

// rename
int chName(CMD* cmd, pid_t* killPID);

#endif
