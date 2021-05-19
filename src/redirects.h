
#include <stdbool.h>

// Headerfile for shell redirection functions

#ifndef REDIRECTS_H
#define REDIRECTS_H

int checkRedirection(int lgt, char** lst, bool* in, int* out);
int getRedirectionFile(int lgt, char** lst, char* inFile, char* outFile, bool detached);
void cleanRedirectFiles(char* inFile, char* outFile);

#endif
