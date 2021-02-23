
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "redirects.h"

// Shell redirection functions

int checkRedirection(int lgt, char** lst, bool* in, int* out) {
   // Check args if redirection is required
   for (int i=0; i < lgt; ++i) {
      if (!strcmp(lst[i], "<")) {
         *in = true;
      } else if (!strcmp(lst[i], ">")) {
         if (*out != 0) {
            printf("Error. Mixed use of \">\" and \">>\" redirection\n");
            return 1;
         } else {
            *out = 1;
         }
      } else if (!strcmp(lst[i], ">>")) {
         if (*out != 0) {
            printf("Error. Mixed use of \">\" and \">>\" redirection\n");
            return 2;
         } else {
            *out = 2;
         }
      }
   }
   return 0;
}

int getRedirectionFile(int lgt, char** lst, char* inFile, char* outFile, bool detached) {
   // Get the filenames for stdin/stdout redirection
   bool in, out;
   in = out = false;
   
   for (int i=0; i < lgt; ++i) {
      if (!in && !strcmp(lst[i], "<")) {
         // If < detected
         // Check for correct arg
         if (i + 1 >= lgt || !strcmp(lst[i + 1], "&") || !strcmp(lst[i + 1], "<") || !strcmp(lst[i + 1], ">") || !strcmp(lst[i + 1], ">>")) {
            printf("Error. Incorrect arguments for redirection\n");
            return 1;
         } else {
            strcpy(inFile, lst[i + 1]);
         }
         in = true;
      } else if (!out && (!strcmp(lst[i], ">") || !strcmp(lst[i], ">>"))) {
         // if > or >> detected
         // Check for correct args
         if (i + 1 >= lgt || !strcmp(lst[i + 1], "&") || !strcmp(lst[i + 1], "<") || !strcmp(lst[i + 1], ">") || !strcmp(lst[i + 1], ">>")) {
            printf("Error. Incorrect arguments for redirection\n");
            return 1;
         } else {
            strcpy(outFile, lst[i + 1]);
         }
         out = true;
      }
   }
   return 0;
}

void cleanRedirectFiles(char* inFile, char* outFile) {
   // Clean redirection files
   strcpy(inFile, "");
   strcpy(outFile, "");
}
