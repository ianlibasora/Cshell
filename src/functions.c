
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
#include <sys/wait.h>

#include "functions.h"
#include "enviroments.h"

#define MAXHOST 100
#define MAXINPUT 500
#define COLBLUE "\x1B[34m"
#define COLGREEN "\x1b[32m"
#define COLRESET "\x1b[0m"

// Functions for main.c shell operation

char* promptInput() {
   char host[MAXHOST];

   char* uName = getenv("USER");
   gethostname(host, MAXHOST);
   char* cwd = getenv("PWD");//Note: cd will handle if new cwd will be invalid

   printf("%s%s@%s%s:", COLGREEN, uName, host, COLRESET);//Print username@hostmachine
   printf("%s%s%s$ ", COLBLUE, cwd, COLRESET);//Print cwd

   static char inp[MAXINPUT];
   fgets(inp, MAXINPUT, stdin);
   return inp;
}

int splitString(char* str, char** lst, int max) {
   char* arg;
   int i = 0;//lst index / final used length
   
   // ------ REFERENCE NOTES PAGE ------
   arg = strtok(str, " \t\n");
   while (arg != NULL && i < max) {
      lst[i] = calloc(strlen(arg), sizeof(char));
      strcpy(lst[i], arg);
      ++i;

      arg = strtok(NULL, " \t\n");
   }
   // Set last element NULL
   lst[i] = NULL;

   return i;
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
