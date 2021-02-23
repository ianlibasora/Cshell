
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// cd command

int cd(int lgt, char** inp, bool detached) {
   if (lgt == 1) {
      printf("%s\n", getenv("PWD"));
      return 0;
   }

   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         if (lgt == 2) {
            // Case: `cd &`
            printf("%s\n", getenv("PWD"));
         } else {
            changeDir(inp[1]);
         }
         exit(0); 
      } else if ( pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing

   } else {
      changeDir(inp[1]);
   }
   return 0;
}

void changeDir(char* path) {
   if (chdir(path) == -1) {
      printf("cd error. %s is an invalid directory.\n", path);
   } else {
      setShellPath("PWD");
   }
}
