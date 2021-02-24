
#include <stdbool.h>

// Headerfile for shell command functions

// cd
int cd(int lgt, char** inp, bool detached);
void changeDir(char* path);

// echo
void echo(int lgt, char** inp, char* outFile, int out, bool detached);
void echoRedirect(int lgt, char** lst, char* outFile, int out);

// environ
void listENV(char** envs, char* outFile, int out, bool detached);
void listENVRedirect(char** envs, char* outFile, int out);

// dir
void dir(int lgt, char** lst, char* outFile, int out, bool detached);
void ls(char* path);
void lsRedirected(char* path, char* outFile, int out);

// fallback execution
int fallbackChild(char** lst);

// pause
void pauseShell();

// Help
void help(char* outFile, int out, bool detached);
void outputHelp();
void helpRedirect(char* outFile, int out);
