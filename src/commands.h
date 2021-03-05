
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
int pauseShell();

// Help
int help(char* outFile, int out, bool detached);
int promptHelp();
int helpRedirect(char* outFile, int out);
void getHelpPath(char* fName);
