
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"

// Default fallback system call function when command is unknown

void fallbackChild(char** lst) {
   // Fork and execute non internal program detached
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      execvp(lst[0], lst);

      exit(0);
   } else if (pid == -1) {
      printf("Error. Fork error occured\n");
      exit(1);
   }
   // Parent does nothing
}
