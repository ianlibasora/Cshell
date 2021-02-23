
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// environ command, display all environment variables

void listENV(int lgt, char** lst, char** envs, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));
         
         for (int i=0; envs[i]; ++i) {
            printf("%s\n", envs[i]);
         }
         exit(0);
      } else if ( pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Normal non detached operation
      for (int i=0; envs[i]; ++i) {
         printf("%s\n", envs[i]);
      }
   }  
}
