
/*----------------------------------
STATEMENT OF NON-PLAGIARISM

I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

Student Number: 19307361
Student Name: Joseph Libasora
-----------------------------------*/

#include <stdbool.h>

// Headerfile for shell redirection functions

int checkRedirection(int lgt, char** lst, bool* in, int* out);
int getRedirectionFile(int lgt, char** lst, char* inFile, char* outFile, bool detached);
void cleanRedirectFiles(char* inFile, char* outFile);
