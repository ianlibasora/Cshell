
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
#define MAXPATH 250

// Help command

// ----- NEED TO ADD MORE FILTER ------

void help(char* outFile, int out, bool detached) {
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
   char* helpFile = calloc(MAXPATH, sizeof(char));
   getHelpPath(helpFile);

   FILE* fPtr = fopen(helpFile, "r");
   if (fPtr != NULL) {
      fgets(line, MAXLINE, fPtr);
      while (!feof(fPtr)) {
         lines[lgt] = calloc(strlen(line), sizeof(char));
         line[strlen(line) - 1] = '\0';//Trim trailling \n
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
      printf("Error. Error accessing %s\n", helpFile);
      return 1;
   }
   fclose(fPtr);

   // More filter
   short unsigned int row, col;
   getTermSize(&row, &col);
   int bufferEnd = 0;// Count of number of buffer rows used by printing
   int i = 0;// Index of lines array
   bool overflow = false;
   int offset = 0;

   while (i < lgt) {
      if (overflow || bufferEnd >= row) {
         // Reached max amount of available rows on the screen
         bufferEnd = 0;
         overflow = false;

         // Prompt interferes with output
         getchar();
      }

      if (strlen(lines[i]) > col) {
         offset = calcOffset(strlen(lines[i]), col);
         if (bufferEnd + offset >= row) {
            // Account for cases of lines overflow
            overflow = true;
         } else {
            printf("%s", lines[i]);
            // If not final print before buffering, print \n 
            // This is to not cause a \n with getchar()
            if (bufferEnd + offset < row) {
               printf("\n");
            }
            
            bufferEnd += offset;
            ++i;
         }
      } else if (bufferEnd + 1 == row) {
         // Case: Final print before buffering will trigger
         // Dont print new line
         // This is to not cause a \n with getchar()
         printf("%s", lines[i]);
         ++i;
         ++bufferEnd;
      } else {
         printf("%s\n", lines[i]);
         ++i;
         ++bufferEnd;
      }
   }

   // Clean memory used
   clearArgs(lgt, lines);
   free(lines);
   free(helpFile);
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

int calcOffset(int lgt, int maxBuffer) {
   int out = 1;
   while (lgt > maxBuffer) {
      lgt -= maxBuffer;
      ++out;
   }
   return out;
}
