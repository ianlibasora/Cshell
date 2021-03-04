
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "commands.h"

// Pause command, sleep till `enter` key from user

void pauseShell() {
   // Hold until the user presses `enter`
   // Uses the getpass() to stop input echo
   char* tmp = getpass("Press ENTER to continue ");
   free(tmp);
}
