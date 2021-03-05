
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"

// Pause command, sleep till `enter` key from user

int pauseShell() {
   // Hold until the user presses `enter`
   // Uses the getpass() to stop input echo
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));

      char* tmp = getpass("Press ENTER to continue ");
      free(tmp);
      exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      exit(1);
   } else {
      // Parent

      // Pause is forked into a child process, but main process still waits
      // Mirrors how the `sleep` command forks into a new process with `bash`
      wait(NULL);
   }
   return 0;
}
