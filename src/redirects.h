
#include <stdbool.h>

#include "cmd.h"

// Headerfile for shell redirection functions

#ifndef REDIRECTS_H
#define REDIRECTS_H

int checkRedirection(CMD* cmd);
int getRedirectionFile(CMD* cmd);

#endif
