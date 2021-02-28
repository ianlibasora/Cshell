
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

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
void fallbackChild(char** lst);

// pause
void pauseShell();

// Help
void help(char* outFile, int out, bool detached);
int promptHelp();
void helpRedirect(char* outFile, int out);
int calcOffset(int lgt, int maxBuffer);
