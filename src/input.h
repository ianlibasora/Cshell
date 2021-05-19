
#include <stdbool.h>
#include "cmd.h"

// Headerfile for input handler functions

#ifndef INPUT_H
#define INPUT_H

char* promptInput(bool prompt);
int splitString(char* str, CMD* cmd);
bool checkInvalidString(char* str);

#endif
