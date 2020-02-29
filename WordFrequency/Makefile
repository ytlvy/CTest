C_OBJS = wordfreq.o list.o
ASM_OBJS =
OBJS = $(C_OBJS) $(ASM_OBJS)

LFLAGS = -02 -g
CFLAGS = -I . -02 -g -Wall
SFLAGS = -I . -02 -g -Wall
DEPENDFLAGS = -I . -M


wordfreq:$(C_OBJS)
	clang $(LFLAGS) -o wordfreq $(OBJS)

.S.o:
	clang $(SFLAGS) -c $<

.c.o:
	clang $(CFLAGS) -c $<

clean:
	-rm -f *.o *~ wordfreq

depend:
	rm -f .depend
	$(CC) $(DEPENDFLAGS) $(C_OBJS:.o=.c) > .depend

ifeq (.depend, $(wildcard .depend))
include .depend
endif