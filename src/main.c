
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "functions.h"// Shell operation functions
#include "commands.h"// Shell commands
#include "enviroments.h"// Enviroment variable manipulation functions
#include "redirects.h"// Shell redirection functions
#include "sigFunctions.h"// Signal handling functions
#include "input.h"// Input handler functions
#include "cmd.h"// CMD struct handling

#define MAXPATH 250

sigjmp_buf buf;

int main(int argc, char* argv[]) {
   bool prompt;
   if (argc > 1) {
      // If argv supplied, run in batch mode
      if (batchRunner(argv[1])) {
         // If error occured
         exit(1);
      }
      prompt = false;
   } else {
      prompt = true;
   }

   static char cwd[MAXPATH];
   getcwd(cwd, MAXPATH);
   setenv("PWD", cwd, 1);// Ensure that cwd is initialised properly
   setExePath();// Assign the absolute path to the shell executable

   // ------ Shell signal handling ------
   // When shell enters a command execution section, signal handling becomes active
   // If a SIGINT were to be raised, the signal handler will reset the loop, and kill the child process
   // Only used for commands `Always Children`
   // Note: will not kill detached processes due to the `active` flag being false
   bool active = false;// Bool to state if command execution in progress
   pid_t killPID;// PID of active process

   // ------ Shell command handling ------
   char* inp;// Input string pointer
   CMD cmd;
   cmd.lgt = 0;
   cleanCMD(&cmd, &killPID);

   // Note:
   // All commands, excluding `quit`, `cd`, `clear`, `environ` run as children of the parent process
   // These are refered to as `Non-Always` and `Always` children commands
   // Detachment is determined by if the parent process should wait for the child process
   // cd however is still able to be run detached

   bool run = true;
   while (run) {
      // ---------- REFERENCE BLOCK ---------
      // Code snippet from: Randal E. Bryant, David R. O’Hallaron - Computer Systems. A Programmer’s Perspective [3rd ed.] (2016, Pearson)
      // Pg 811, fig 8.44
      // Code contains minor modifications to fit the purpose of a shell signal handler
      // Function source code located in `signalFunctions.c`

      if (!sigsetjmp(buf, 1)) {
         Signal(SIGINT, handler);
      } else {
         // Additional signal handling for (non-detached) child process SIGINT
         // Kills the unreapable process from SIGINT
         if (active && killPID != 0) {
            kill(killPID, SIGTERM);
         }
         active = false;
         // If SIGINT triggers, cleanup shell before new prompt
         cleanCMD(&cmd, &killPID);
      }
      // ---------- END BLOCK ---------

      // Clean any zombie processes, prompt user for new input
      cleanChildren();
      inp = promptInput(prompt);
      if (feof(stdin)) {
         break;
      }

      // Parse input into CMD struct
      if (parseCMD(inp, &cmd) != 0) {
         cleanCMD(&cmd, &killPID);
         continue;
      }

      // Non-Always children commands
      if (!strcmp(cmd.args[0], "quit")) {
         break;
      } else if (!strcmp(cmd.args[0], "cd")) {
         cd(&cmd);
      } else if (!strcmp(cmd.args[0], "clr")) {
         system("clear");
      } else if (!strcmp(cmd.args[0], "environ")) {
         listENV(&cmd);
      } 
      // Always children commands
      else if (!strcmp(cmd.args[0], "dir")) {
         active = true;
         dir(&cmd, &killPID);
      } else if (!strcmp(cmd.args[0], "echo")) {
         active = true;
         echo(&cmd, &killPID);
      } else if (!strcmp(cmd.args[0], "pause")) {
         active = true;
         pauseShell(&cmd, &killPID);
      } else if (!strcmp(cmd.args[0], "help")) {
         active = true;
         help(&cmd, &killPID);
      } else if (!strcmp(cmd.args[0], "rename")) {
         active = true;
         chName(&cmd, &killPID);
      } else {
         active = true;
         fallback(&cmd, &killPID);
      }

      if (!cmd.detached) {
         // If not detached
         wait(NULL);
      }
      active = false;
      cleanCMD(&cmd, &killPID);
   }
   printf("Quitting myshell\n");
   exit(0);
}
