
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
int echo(int lgt, char** inp, char* outFile, int out, bool detached);
int echoRedirect(int lgt, char** lst, char* outFile, int out);

// environ
int listENV(char* outFile, int out, bool detached);
int listENVRedirect(char** envs, char* outFile, int out);

// dir
int dir(int lgt, char** lst, char* outFile, int out, bool detached);
int ls(char* path);
int lsRedirected(char* path, char* outFile, int out);

// fallback execution
int fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out, bool detached);

// pause
void pauseShell();

// Help
void help(char* outFile, int out, bool detached);
int promptHelp();
void helpRedirect(char* outFile, int out);
int calcOffset(int lgt, int maxBuffer);
