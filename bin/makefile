
# STATEMENT OF NON-PLAGIARISM

# I hereby declare that all information in this assignment has been obtained and presented in accordance with academic rules and ethical conduct and the work I am submitting in this document, except where I have indicated, is my own work.

# Student Number: 19307361
# Student Name: Joseph Libasora

# Primary makefile responsible for builds/cleans/runs of c code and executables

CFILES = $(wildcard ../src/*.c)
OFILES = $(patsubst %.c, %.o, $(CFILES))
EXEFILE = ./myshell

build: $(EXEFILE)
	@true

$(EXEFILE): $(OFILES)
	gcc -Werror -Wall -std=gnu11 -o $(EXEFILE) $(OFILES)

clean:
	rm -f $(OFILES) $(EXEFILE) *~

run: $(EXEFILE)
	./myshell

.PHONY: run build clean
