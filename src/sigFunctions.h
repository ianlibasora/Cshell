
// Headerfile for signal handler functions

#ifndef SIGFUNCTIONS_H
#define SIGFUNCTIONS_H

void* Signal(int signum, void (*handler)(int));
void handler(int sig);
void disabledHandler(int sig);
void maskSIGINT();

#endif
