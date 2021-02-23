
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"
#include "enviroments.h"

// Default fallback system call function when command is unknown

int fallbackChild(char** lst) {

   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      execvp(lst[0], lst);

      exit(0);
   } else {
      // Parent, wait for child to exec
      wait(NULL);
      return 0;
   }
}
