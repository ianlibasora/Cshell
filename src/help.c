
/*----------------------------------
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"
#include "functions.h"

#define MAXLINE 500

// Help command

// ----- NEED TO ADD MORE FILTER ------

void help(char* outFile, int out, bool detached) {
   short unsigned int row, col;
   short unsigned int* rowPtr = &row;
   short unsigned int* colPtr = &col;
   getTermSize(rowPtr, colPtr);
   
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         // Choose between either normal/redirection operation
         out == 0 ? promptHelp(): helpRedirect(outFile, out);
         exit(0);         
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Choose between either normal/redirection operation
      out == 0 ? promptHelp(): helpRedirect(outFile, out);
   }
}

int promptHelp() {
   char line[MAXLINE];
   int alloc = 100;
   int lgt = 0;
   char** lines = calloc(alloc, sizeof(char*));
   if (lines == NULL) {
      printf("Error. Memory allocation failed\n");
      return 2;
   }

   // Read file contents into array
   FILE* fPtr = fopen("../manual/readme.md", "r");
   if (fPtr != NULL) {
      fgets(line, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         lines[lgt] = calloc(strlen(line), sizeof(char));
         strcpy(lines[lgt], line);
         fgets(line, MAXLINE, fPtr);
         ++lgt;

         if (lgt >= alloc) {
            alloc += 100;
            lines = realloc(lines, alloc * sizeof(char*));
            if (lines == NULL) {
               printf("Error. Memory reallocation failed\n");
               return 3;
            }
         }
      }
   } else {
      printf("Error. Error accessing ../manual/readme.md\n");
      return 1;
   }
   fclose(fPtr);

   // ------------- INSERT MORE FILTER ---------------

   for (int i=0; i < lgt; ++i) {
      printf("%s", lines[i]);
   }


   // Clean memory used
   clearArgs(lgt, lines);
   free(lines);
   return 0;
}

void helpRedirect(char* outFile, int out) {
   char op[4];
   strcpy(op, (out == 1 ? "w": "a"));
   char line[MAXLINE];

   FILE* outFilePtr = fopen(outFile, op);
   if (outFilePtr != NULL) {
      FILE* manFilePtr = fopen("../manual/readme.md", "r");
      if (manFilePtr != NULL) {
         fgets(line, MAXLINE, manFilePtr);
         while (!feof(manFilePtr)) {
            fprintf(outFilePtr, "%s", line);
            fgets(line, MAXLINE, manFilePtr);
         }
      } else {
         printf("Error. Error accessing ../manual/readme.md\n");
      }
      fclose(manFilePtr);
   } else {
      printf("Error. Error accessing %s\n", outFile);
   }
   fclose(outFilePtr);
}
