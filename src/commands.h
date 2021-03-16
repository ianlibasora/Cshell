
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdbool.h>

// Headerfile for shell command functions

// cd
int cd(int lgt, char** inp, bool detached);
void changeDir(char* path);

// echo
int echo(int lgt, char** inp, char* outFile, int out, int* killPID);
int echoRedirect(int lgt, char** lst, char* outFile, int out);

// environ
int listENV(char* outFile, int out);
int listENVRedirect(char** envs, char* outFile, int out);

// dir
int dir(int lgt, char** lst, char* outFile, int out, int* killPID);
int ls(char* path);
int lsRedirected(char* path, char* outFile, int out);

// fallback execution
int fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out, int* killPID);
bool checkInterpreter(char* arg);

// pause
int pauseShell(int* killPID);

// Help
int help(char* outFile, int out, int* killPID);
int promptHelp();
int helpRedirect(char* outFile, int out);
void getHelpPath(char* fName);
