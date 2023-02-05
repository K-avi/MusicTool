CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter -std=c17
#CFLAGS = -g -Wno-unused-parameter
CC = gcc

.PHONY:	all clean

all: $(ALLPROGS)
progs: $(PROGRAMS)

test: scalegen.o harmo.o parsing.o  user_info.o globals.o init.o triadgen.o rand.o misc.o triadprint.o parseloop.o writeenv.o syntaxcheck.o dodecseries.o genfuncs.o chordgen.o chordprint.o main_test.o 
	$(CC) -o $@ $(CFLAGS) $^

MusicTool: scalegen.o init.o harmo.o parsing.o user_info.o globals.o triadgen.o triadprint.o rand.o misc.o parseloop.o writeenv.o syntaxcheck.o dodecseries.o genfuncs.o chordgen.o chordprint.o main_interpreter.o
	$(CC) -o $@ $(CFLAGS) $^


smtool: scalegen.o init.o harmo.o parsing.o user_info.o globals.o triadgen.o triadprint.o rand.o misc.o parseloop.o writeenv.o syntaxcheck.o dodecseries.o genfuncs.o chordgen.o chordprint.o main_command.o
	$(CC) -o $@ $(CFLAGS) $^


%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(ALLPROGS)
