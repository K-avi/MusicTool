

CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
#CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   test MusicTool

.PHONY:	all clean

all: $(PROGRAMS)

test: scalegen.o harmo.o parsing.o scaleloop.o user_info.o globals.o init.o main_test.o
	$(CC) -o $@ $(CFLAGS) $^



MusicTool: scalegen.o init.o scaleloop.o harmo.o parsing.o user_info.o globals.o main.o
	$(CC) -o $@ $(CFLAGS) $^

#Ou plus simplement
%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)