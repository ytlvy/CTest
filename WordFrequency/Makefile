C_OBJS = wordfreq.o list.o
ASM_OBJS = wl_print_numerical.o
OBJS = $(C_OBJS) $(ASM_OBJS)

LFLAGS = -O2 -g -marm
CFLAGS = -I . -O2 -g -Wall -marm
SFLAGS = -I . -O2 -g -Wall -marm
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