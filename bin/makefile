
# ***REMOVED***

# ***REMOVED***

# ***REMOVED***
# ***REMOVED***

# Makefile responsible for builds/cleans/runs of c code and executables

OFILES = ../src/main.o ../src/functions.o ../src/cd.o ../src/echo.o ../src/environ.o ../src/default.o ../src/dir.o ../src/envFunctions.o ../src/pause.o ../src/batch.o ../src/redirection.o ../src/help.o
EXEFILE = ./myshell

build: $(EXEFILE)
	@true

$(EXEFILE): $(OFILES)
	gcc -Werror -Wall -std=c11 -o $(EXEFILE) $(OFILES)

clean:
	rm -f $(OFILES) $(EXEFILE) *~

run: $(EXEFILE)
	./myshell

.PHONY: run build clean
