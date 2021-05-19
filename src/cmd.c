
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cmd.h"
#include "input.h"

// Functions for CMD structure handling

int parseCMD(char* inp, CMD* cmd) {
   if (checkInvalidString(inp)) {
      // If error, restart loop
      return 1;
   }
   if (splitString(inp, cmd) != 0) {
      // If error, restart loop
      return 2;
   }
   
   return 0;
}
