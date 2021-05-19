
#include <stdbool.h>

// Headerfile for functions handling shell operation (main.c)

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void clearArgs(int lgt, char** lst);
void cleanChildren();

// Matchmode function
int batchRunner(char* fName);

#endif
