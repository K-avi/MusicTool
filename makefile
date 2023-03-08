CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter -std=c11
#CFLAGS = -g -Wno-unused-parameter
CC = gcc
ALLPROGS= test MusicTool smtool
PROGRAMS= MusicTool smtool

.PHONY:	all clean

all: $(ALLPROGS)
progs: $(PROGRAMS)

test: 
	$(MAKE) -C src/ ../test

MusicTool: 
	$(MAKE) -C src/ ../MusicTool


smtool: 
	$(MAKE) -C src/ ../smtool


clean:
	rm -f src/*.o *~ $(ALLPROGS)
