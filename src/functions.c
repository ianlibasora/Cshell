
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
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "functions.h"
#include "enviroments.h"

#define MAXHOST 100
#define MAXINPUT 500
#define COLBLUE "\x1B[34m"
#define COLGREEN "\x1b[32m"
#define COLRESET "\x1b[0m"

// Functions for main.c shell operation

char* promptInput(bool prompt) {
   char host[MAXHOST];

   char* uName = getenv("USER");
   gethostname(host, MAXHOST);
   char* cwd = getenv("PWD");// Note: cd command handles invalid cwd

   if (prompt) {
      printf("%s%s@%s%s:", COLGREEN, uName, host, COLRESET);// Print username@hostmachine
      printf("%s%s%s$ ", COLBLUE, cwd, COLRESET);// Print cwd
   }

   static char inp[MAXINPUT];
   fgets(inp, MAXINPUT, stdin);
   return inp;
}

int splitString(char* str, int* lgt, char** lst, int max) {
   char* arg;
   int i = 0;// lst index / final used length

   arg = strtok(str, " \t\n");
   while (arg != NULL && i < max) {
      lst[i] = calloc(strlen(arg), sizeof(char));
      strcpy(lst[i], arg);
      ++i;

      arg = strtok(NULL, " \t\n");
   }
   if (i == max) {
      fprintf(stderr, "Warning. Max number of arguments reached. Command invalid and rejected\n");
      return 1;
   }

   // Set last element NULL
   lst[i] = NULL;
   *lgt = i;
   return 0;
}

void clearArgs(int lgt, char** lst) {
   // Free memory allocated in array
   for (int i=0; i < lgt; ++i) {
      free(lst[i]);
   }
}

void cleanChildren() {
   // Clean any present zombie processes
   pid_t pid = waitpid(-1, NULL, WNOHANG);
   while (pid != 0 && pid != -1) {
      printf("Process %d ended\n", pid);
      pid = waitpid(-1, NULL, WNOHANG);
   }
}

bool checkInvalidString(char* str) {
   // Check if string contains content and is not just whitespace characters
   for (int i=0; i < strlen(str); ++i) {
      if (isspace(str[i]) == 0) {
         return false;
      }
   }
   return true;
}

int batchRunner(char* fName) {
   FILE* fPtr = fopen(fName, "r");

   if (fPtr == NULL) {
      fprintf(stderr, "Error. Error occured accessing %s\n", fName);
      return 1;
   }
   if (dup2(fileno(fPtr), 0) == -1) {
      fprintf(stderr, "Error. Error occured accessing %s\n", fName);
      return 1;
   }
   fclose(fPtr);
   return 0;
}
