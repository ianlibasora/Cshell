
#include <stdbool.h>

// Headerfile for shell command functions

// cd
int cd(int lgt, char** inp, bool detached);
void changeDir(char* path);

// echo
void echo(int lgt, char** inp, bool detached);

// environ
void listENV(int lgt, char** lst, char** envs, bool detached);

// dir
int dir(int lgt, char** lst, char* outFile, int out, bool detached);
void ls(char* path);
void lsRedirected(char* path, char* outFile, int out);

// fallback execution
int fallbackChild(char** lst);

// pause
void pauseShell();
