
# ***REMOVED***

# ***REMOVED***

# ***REMOVED***
# ***REMOVED***

# Root directory makefile
# This file is just for ease of use and just calls the makefile inside `bin`

build:
	$(MAKE) -C bin build

clean:
	$(MAKE) -C bin clean

run:
	$(MAKE) -C bin run

.PHONY: build clean run
