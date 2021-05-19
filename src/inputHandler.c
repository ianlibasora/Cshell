
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "input.h"
#include "cmd.h"

#define MAXHOST 100
#define MAXINPUT 500
#define COLBLUE "\x1B[34m"
#define COLGREEN "\x1b[32m"
#define COLRESET "\x1b[0m"

// Input handler functions

char* promptInput(bool prompt) {
   char host[MAXHOST];

   if (prompt) {
      char* uName = getenv("USER");
      gethostname(host, MAXHOST);
      char* cwd = getenv("PWD");// Note: cd command handles invalid cwd
      printf("%s%s@%s%s:", COLGREEN, uName, host, COLRESET);// Print username@hostmachine
      printf("%s%s%s$ ", COLBLUE, cwd, COLRESET);// Print cwd
   }

   static char inp[MAXINPUT];
   fgets(inp, MAXINPUT, stdin);
   return inp;
}

int splitString(char* str, CMD* cmd) {
   char* arg;
   int i = 0;// lst index / final used length

   arg = strtok(str, " \t\n");
   while (arg != NULL && i < CMDMAXARGS) {
      cmd->args[i] = calloc(strlen(arg), sizeof(char));
      strcpy(cmd->args[i], arg);
      ++i;

      arg = strtok(NULL, " \t\n");
   }
   if (i == CMDMAXARGS) {
      fprintf(stderr, "Warning. Max number of arguments reached. Command invalid and rejected\n");
      return 1;
   }

   // Set last element NULL
   cmd->args[i] = NULL;
   cmd->lgt = i;
   return 0;
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
