

CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
#CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   smtool MusicTool

.PHONY:	all clean

all: $(PROGRAMS)

test: scalegen.o harmo.o parsing.o  user_info.o globals.o init.o chordgen.o rand.o misc.o chordprint.o parseloop.o writeenv.o syntaxcheck.o main_test.o 
	$(CC) -o $@ $(CFLAGS) $^

MusicTool: scalegen.o init.o harmo.o parsing.o user_info.o globals.o chordgen.o chordprint.o rand.o misc.o parseloop.o writeenv.o syntaxcheck.o main_interpreter.o
	$(CC) -o $@ $(CFLAGS) $^


smtool: scalegen.o init.o harmo.o parsing.o user_info.o globals.o chordgen.o chordprint.o rand.o misc.o parseloop.o writeenv.o syntaxcheck.o main_command.o
	$(CC) -o $@ $(CFLAGS) $^
	
%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
