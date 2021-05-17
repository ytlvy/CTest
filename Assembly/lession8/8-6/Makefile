C_OBJS=fixedfuncs.o
ASM_OBJS=sincosmain.o sincos.o 
OBJS=$(C_OBJS) $(ASM_OBJS)

CC=gcc
LFLAGS=-O0 -g
CFLAGS=-I. -O0 -g -Wall
SFLAGS=-I. -O0 -g -Wall
DEPENDFLAGS=-I. -M

sincosmain: $(OBJS)
	$(CC) $(LFLAGS) -o sincosmain $(OBJS)

.S.o:
	$(CC) $(SFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ sincosmain

# make depend will create a file ".depend" with all the dependencies
depend:
	rm -f .depend
	$(CC) $(DEPENDFLAGS) $(C_OBJS:.o=.c) > .depend

# if we have a .depend file include it
ifeq (.depend, $(wildcard .depend))
include .depend
endif