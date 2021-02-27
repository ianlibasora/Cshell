
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

int help(char* outFile, int out, bool detached) {
   short unsigned int row, col;
   getTermSize(&row, &col);
   int lgt = 100;
   char** lines = calloc(lgt, sizeof(char*));  
   if (readHelpFile(&lgt, lines) != 0) {
      return 1;
   }

   // if (detached) {
   //    pid_t pid = fork();
   //    if (pid == 0) {
   //       // Child
   //       setShellENV("PARENT", getenv("SHELL"));

   //       // Choose between either normal/redirection operation
   //       out == 0 ? outputHelp(): helpRedirect(outFile, out);
   //       exit(0);         
   //    } else if (pid == -1) {
   //       printf("Error. Fork error occured\n");
   //       exit(1);
   //    }
   //    // Parent does nothing
   // } else {
   //    // Choose between either normal/redirection operation
   //    out == 0 ? outputHelp(): helpRedirect(outFile, out);
   // }

   // Clean used memory
   clearArgs(lgt, lines);
   free(lines);
}

void outputHelp() {
   char line[MAXLINE];
   FILE* fPtr = fopen("../manual/readme.md", "r");
   if (fPtr != NULL) {
      fgets(line, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         printf("%s", line);
         fgets(line, MAXLINE, fPtr);
      }
   } else {
      printf("Error. Error accessing ../manual/readme.md\n");
   }
   fclose(fPtr);
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

int readHelpFile(int* lgt, char** lines) {
   int i = 0;
   int max = *lgt;//Initial array allocation
   char tmpLine[MAXLINE];
   
   FILE* fPtr = fopen("../manual/readme.md", "r");
   if (fPtr != NULL) {
      fgets(tmpLine, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         lines[i] = calloc(strlen(tmpLine), sizeof(char));
         strcpy(lines[i], tmpLine);
         fgets(tmpLine, MAXLINE, fPtr);
         ++i;

         // Check if more lines required
         if (i >= max) {
            max += 100;
            lines = realloc(lines, max * sizeof(*lines));
         }
      }
      fclose(fPtr);
      // Truncate over allocated memory
      lines = realloc(lines, i * sizeof(*lines));
   } else {
      printf("Error. Error accessing ../manual/readme.md\n");
      fclose(fPtr);
      return 1;
   }
   *lgt = i;//Return array length
   return 0;
}
