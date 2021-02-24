
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

#include <stdbool.h>

// Headerfile for functions handling shell operation (main.c)

char* promptInput();
int splitString(char* str, char** lst, int max);
void clearArgs(int lgt, char** lst);
void cleanChildren();

// BatchRunner.c functions
int batchRunner(char* fName);
