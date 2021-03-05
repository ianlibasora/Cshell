
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

#include "redirects.h"

// Shell redirection/detach functions

int checkRedirection(int lgt, char** lst, bool* in, int* out) {
   // Check args if redirection is required
   // Return 0 on sucess
   for (int i=0; i < lgt; ++i) {
      if (!strcmp(lst[i], "<")) {
         *in = true;
      } else if (!strcmp(lst[i], ">")) {
         if (*out != 0) {
            fprintf(stderr, "Error. Mixed use of \">\" and \">>\" redirection\n");
            return 1;
         } else {
            *out = 1;
         }
      } else if (!strcmp(lst[i], ">>")) {
         if (*out != 0) {
            fprintf(stderr, "Error. Mixed use of \">\" and \">>\" redirection\n");
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
   // Return 0 on sucess
   bool in, out;
   in = out = false;
   
   for (int i=0; i < lgt; ++i) {
      if (!in && !strcmp(lst[i], "<")) {
         // If < detected
         // Check for correct arg
         if (i + 1 >= lgt || !strcmp(lst[i + 1], "&") || !strcmp(lst[i + 1], "<") || !strcmp(lst[i + 1], ">") || !strcmp(lst[i + 1], ">>")) {
            fprintf(stderr, "Error. Incorrect arguments for redirection\n");
            return 1;
         } else {
            strcpy(inFile, lst[i + 1]);
         }
         in = true;
      } else if (!out && (!strcmp(lst[i], ">") || !strcmp(lst[i], ">>"))) {
         // if > or >> detected
         // Check for correct args
         if (i + 1 >= lgt || !strcmp(lst[i + 1], "&") || !strcmp(lst[i + 1], "<") || !strcmp(lst[i + 1], ">") || !strcmp(lst[i + 1], ">>")) {
            fprintf(stderr, "Error. Incorrect arguments for redirection\n");
            return 2;
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

bool checkDetached(int lgt, char** lst) {
   // Check args if running retached
   for (int i=0; i < lgt; ++i) {
      if (!strcmp(lst[i], "&")) {
         return true;
      }
   }
   return false;
}
