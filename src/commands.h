
#include <stdbool.h>

// Headerfile for shell command functions

int cd(int lgt, char** inp, bool detached);
void changeDir(char* path);
void echo(int lgt, char** inp, bool detached);
void listENV(int lgt, char** lst, char** envs, bool detached);
int dir(int lgt, char** lst, int out, bool detached);
void ls(char* path);
int fallbackChild(char** lst);
void pauseShell();
