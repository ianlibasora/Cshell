
#include <stdbool.h>

// Headerfile for shell redirection functions

int checkRedirection(int lgt, char** lst, bool* in, int* out);
void getRedirectionFile(int lgt, char** lst, char* inFile, char* outFile, bool detached);
