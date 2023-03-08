PROGRAMS:= ../MusicTool ../smtool
ALLPROGS:= ../test ../MusicTool ../smtool

CFLAGS = -g -D_DEFAULT_SOURCE -Wall -Wextra -pedantic -Wno-unused-parameter -std=c11
CC := gcc

progs: $(PROGRAMS)
all: $(ALLPROGS)

SRCS:= scalegen.o harmo.o parsing.o  user_info.o globals.o init.o triadgen.o rand.o misc.o triadprint.o parseloop.o writeenv.o syntaxcheck.o dodecseries.o genfuncs.o chordgen.o chordprint.o progbook.o coherand.o


../test: $(SRCS) main_test.o 
	$(CC) -o $@ $(CFLAGS) $^

../MusicTool: $(SRCS) main_interpreter.o
	$(CC) -o $@ $(CFLAGS) $^


../smtool: $(SRCS) main_command.o
	$(CC) -o $@ $(CFLAGS) $^


clean:
	rm -f *.o *~ $(ALLPROGS)

.PHONY:	clean
