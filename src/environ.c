
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// environ command, display all environment variables

void listENV(char** envs, char* outFile, int out, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));
         extern char** environ;//Reloads new environment variables so as to catch the new `PARENT` variable

         if (out == 0) {
            // Run no redirection
            for (int i=0; environ[i]; ++i) {
               printf("%s\n", environ[i]);
            }
         } else {
            // Run redirection
            listENVRedirect(environ, outFile, out);
         }
         exit(0);
      } else if ( pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Normal non detached operation
      if (out == 0) {
         // Run no redirection
         for (int i=0; envs[i]; ++i) {
            printf("%s\n", envs[i]);
         }
      } else {
         // Run redirection
         listENVRedirect(envs, outFile, out);
      }
   }  
}

void listENVRedirect(char** envs, char* outFile, int out) {
   char op[4];
   strcpy(op, (out == 1 ? "w": "a"));

   FILE* fPtr = fopen(outFile, op);
   if (fPtr != NULL) {
      for (int i=0; envs[i]; ++i) {
         fprintf(fPtr, "%s\n", envs[i]);
      }
   } else {
      printf("Error. Error occured accessing %s\n", outFile);
   }
   fclose(fPtr);
}
