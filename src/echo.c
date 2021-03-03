
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "commands.h"
#include "enviroments.h"

// echo command

void echo(int lgt, char** inp, char* outFile, int out, bool detached) {
   if (detached) {
      pid_t pid = fork();
      if (pid == 0) {
         // Child
         setShellENV("PARENT", getenv("SHELL"));

         if (out == 0) {
            // Run no redirection
            int i = 1;
            while (i < lgt && strcmp(inp[i], "&")) {
               printf("%s ", inp[i]);
               ++i;
            }
            printf("\n");
         } else {
            // Run redirection
            echoRedirect(lgt, inp, outFile, out);
         }
         exit(0);
      } else if (pid == -1) {
         printf("Error. Fork error occured\n");
         exit(1);
      }
      // Parent does nothing
   } else {
      // Normal non detached operation
      if (out == 0) {
         // Run no redirection
         for (int i=1; i < lgt; ++i) {
            printf("%s ", inp[i]);
         }
         printf("\n");
      } else {
         // Run redirection
         echoRedirect(lgt, inp, outFile, out);
      }
   }
}

void echoRedirect(int lgt, char** lst, char* outFile, int out) {
   char op[4];
   strcpy(op, (out == 1 ? "w": "a"));

   FILE* fPtr = fopen(outFile, op);
   if (fPtr != NULL) {
      int i = 1;
      while (i < lgt && strcmp(lst[i], "&")) {
         if (!strcmp(lst[i], "<") || !strcmp(lst[i], ">") || !strcmp(lst[i], ">>")) {
            i += 2;
         } else {
            fprintf(fPtr, "%s ", lst[i]);
            ++i;
         }
      }
      fprintf(fPtr, "\n");
   } else {
      printf("Error. Error occured accessing %s\n", outFile);
   }
   fclose(fPtr);
}
