
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
void listENV(char** envs, char* outFile, int out, bool detached);
void listENVRedirect(char** envs, char* outFile, int out);

// dir
void dir(int lgt, char** lst, char* outFile, int out, bool detached);
void ls(char* path);
void lsRedirected(char* path, char* outFile, int out);

// fallback execution
void fallbackChild(int lgt, char** lst, char* inFile, bool in, char* outFile, int out);

// pause
void pauseShell();

// Help
void help(char* outFile, int out, bool detached);
int promptHelp();
void helpRedirect(char* outFile, int out);
int calcOffset(int lgt, int maxBuffer);
