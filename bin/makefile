
# Primary makefile responsible for builds/cleans/runs of c code and executables

CFILES = $(wildcard ../src/*.c)
OFILES = $(patsubst %.c, %.o, $(CFILES))
EXEFILE = ./cshell

build: $(EXEFILE)
	@true

$(EXEFILE): $(OFILES)
	gcc -Werror -Wall -std=gnu11 -o $(EXEFILE) $(OFILES)

clean:
	rm -f $(OFILES) $(EXEFILE) *~

run: $(EXEFILE)
	./cshell

.PHONY: run build clean
