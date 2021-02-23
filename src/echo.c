
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// echo command

void echo(int lgt, char** inp, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         for (int i=1; i < lgt-1; ++i) {
            printf("%s ", inp[i]);
         }
         printf("\n");
         exit(0);
      } else if (pid == -1) {
         printf("Warning. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Normal non detached operation
      for (int i=1; i < lgt; ++i) {
         printf("%s ", inp[i]);
      }
      printf("\n");
   }
}
