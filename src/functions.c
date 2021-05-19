
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "functions.h"
#include "enviroments.h"

// Functions for shell operation

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
