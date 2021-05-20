
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "commands.h"
#include "enviroments.h"
#include "sigFunctions.h"
#include "cmd.h"
#include "redirects.h"

#define MAXPATH 250

// dir command, list contents of directory

int dir(CMD* cmd, pid_t* killPID) {
   // Determine paths to directories
   char path[MAXPATH];
   if (cmd->lgt == 1) {
      strcpy(path, ".");
   } else if (!strcmp(cmd->args[1], "&") || !strcmp(cmd->args[1], "<") || !strcmp(cmd->args[1], ">") || !strcmp(cmd->args[1], ">>")) {
      strcpy(path, ".");
   } else {
      strcpy(path, cmd->args[1]);
   }

   pid_t pid = fork();
   if (pid == 0) {
      // Child
      setShellENV("PARENT", getenv("SHELL"));
      *killPID = getpid();

      if (cmd->detached) {
         // If detached, mask SIGINT
         maskSIGINT();
      }

      // Handle redirection
      if (redirect(cmd) != 0) {
         _exit(2);
      }
      
      ls(path);
      _exit(0);
   } else if (pid == -1) {
      fprintf(stderr, "Error. Fork error occured\n");
      _exit(1);
   }
   // Parent does nothing
   // Waiting/detachment handled by main
   return 0;
}

int ls(char* path) {
   // ---------- REFERENCE BLOCK ---------
   // Based on source material from: https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html

   DIR *dPtr = opendir(path);
   struct dirent *dir;
   if (dPtr) {
      while ((dir = readdir(dPtr)) != NULL) {
         printf("%s\n", dir->d_name);
      }

   } else {
      fprintf(stderr, "Error. Could not open directory %s\n", path);
      return 1;
   }
   closedir(dPtr);
   // ---------- CLOSE BLOCK ----------

   return 0;
}
