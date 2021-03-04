
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "commands.h"

// Pause command, sleep till `enter` key from user

void pauseShell() {
   // Hold until the user presses `enter`
   // Uses the getpass() to stop input echo
   char* tmp = getpass("Press ENTER to continue ");
   free(tmp);
}
