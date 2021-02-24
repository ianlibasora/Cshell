
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

#define MAXLINE 200

// Help command

void help(char* outFile, int out, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         outputHelp();
         exit(0);         
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
      }
      // Parent does nothing
   } else {
      outputHelp();
   }
}

void outputHelp() {
   char line[MAXLINE];
   FILE* fPtr = fopen("../manual/readme.md", "r");
   if (fPtr != NULL) {
      while (!feof(fPtr)) {
         fgets(line, MAXLINE, fPtr);
         printf("%s", line);
      }
   } else {
      printf("Error. Error accessing ../manual/readme.md\n");
   }
   fclose(fPtr);
}
