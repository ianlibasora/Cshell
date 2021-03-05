
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#include "sigFunctions.h"

// Signal handling functions

// ------ REFERENCE FROM 801, 811 OF OS BOOK

// Changes:
// *Signal declaration
// prints to write

sigjmp_buf buf;

void* Signal(int signum, void (*handler)(int)) {
   struct sigaction action, old_action;

   action.sa_handler = handler;
   sigemptyset(&action.sa_mask); /* Block sigs of type being handled */
   action.sa_flags = SA_RESTART; /* Restart syscalls if possible */

   if (sigaction(signum, &action, &old_action) < 0)
      write(STDOUT_FILENO, "System error\n", 11);
   return (old_action.sa_handler);
}

void handler(int sig) {
   siglongjmp(buf, 1);
}

// ------------ END REF BLOCK -----------------
