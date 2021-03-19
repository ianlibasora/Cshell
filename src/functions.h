
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdbool.h>

// Headerfile for functions handling shell operation (main.c)

char* promptInput(bool prompt);
int splitString(char* str, int* lgt, char** lst, int max);
void clearArgs(int lgt, char** lst);
void cleanChildren();
bool checkInvalidString(char* str);

// Matchmode function
int batchRunner(char* fName);
