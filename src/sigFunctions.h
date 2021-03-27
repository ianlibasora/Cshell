
// Headerfile for signal handler functions

void* Signal(int signum, void (*handler)(int));
void handler(int sig);
void disabledHandler(int sig);
void maskSIGINT();
