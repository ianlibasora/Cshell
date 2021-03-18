
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"

// rename command

int chName(int lgt, char** lst, bool detached, int* killPID) {
   if (detached && lgt != 4 || !detached && lgt != 3) {
      fprintf(stderr, "Error. Invalid arguments for rename\n");
      return 1;
   }
   
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // Rename arg[1] to arg[2]
      if (rename(lst[1], lst[2]) != 0) {
         fprintf(stderr, "Error. Unable to rename %s to %s\n", lst[1], lst[2]);
         exit(1);
      }
      exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(2);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}
