
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

// Functions for main.c shell operation

char* promptInput() {
   const char colBlue[] = "\x1B[34m";
   const char colGreen[] = "\x1b[32m";
   const char colReset[] = "\x1b[0m";
   char host[MAXHOST];

   char* uName = getenv("USER");
   gethostname(host, MAXHOST);
   char* cwd = getenv("PWD");//Note: cd will handle if new cwd will be invalid

   printf("%s%s@%s%s:", colGreen, uName, host, colReset);//Print username@hostmachine
   printf("%s%s%s$ ", colBlue, cwd, colReset);//Print cwd

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

      arg = strtok(NULL, " \n");
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
