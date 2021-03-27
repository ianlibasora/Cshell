
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"

// Pause command, sleep till `enter` key from user

int pauseShell(bool detached, int* killPID) {
   // Hold until the user presses `enter`
   // Uses the getpass() to stop input echo
   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      char* tmp = getpass("Press ENTER to continue ");
      free(tmp);
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}
