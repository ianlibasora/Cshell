
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

#define MAXLINE 200

// Help command

// feof

int help(char* outFile, int out, bool detached) {
   char line[MAXLINE];
   FILE* manFilePtr = fopen("../manual/readme.md", "r");
   if (manFilePtr != NULL) {
      while (!feof(manFilePtr)) {
         fgets(line, MAXLINE, manFilePtr);
         printf("%s", line);

      }

   } else {
      printf("Error. Error accessing ../manual/readme.md\n");
   }
   
   fclose(manFilePtr);
}
