
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

// ---------- REFERENCE BLOCK ---------
// Code snippet from: Randal E. Bryant, David R. O’Hallaron - Computer Systems. A Programmer’s Perspective [3rd ed.] (2016, Pearson)
// Pg 811, fig 8.44
// Code contains minor modifications to fit the purpose of a shell signal handler
// Line 30 function definition modified to comply with types
// Line 38 modfied to be async-signal safe

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
// ---------- END BLOCK ---------

void disabledHandler(int sig) {
   // Do nothing
}
