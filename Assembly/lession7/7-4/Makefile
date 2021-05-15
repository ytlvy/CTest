C_OBJS=main.o bigint.o
ASM_OBJS=
OBJS=$(C_OBJS) $(ASM_OBJS)

CC=gcc
LFLAGS=-O2 -g
CFLAGS=-I. -O2 -g -Wall
SFLAGS=-I. -O2 -g -Wall
DEPENDFLAGS=-I. -M

main: $(OBJS)
	$(CC) $(LFLAGS) -o biginttest $(OBJS)

.S.o:
	$(CC) $(SFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ biginttest

# make depend will create a file ".depend" with all the dependencies
depend:
	rm -f .depend
	$(CC) $(DEPENDFLAGS) $(C_OBJS:.o=.c) > .depend

# if we have a .depend file include it
ifeq (.depend, $(wildcard .depend))
include .depend
endif