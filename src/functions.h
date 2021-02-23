
#include <stdbool.h>

// Headerfile for functions handling shell operation (main.c)

char* promptInput();
int splitString(char* str, char** lst, int max);
void clearArgs(int lgt, char** lst);
void cleanChildren();
int checkRedirection(int lgt, char** lst, bool* in, int* out);
void getRedirectionFile(int lgt, char** lst, char* inFile, char* outFile, bool detached);

// BatchRunner.c functions
int batchRunner(char* fName);
