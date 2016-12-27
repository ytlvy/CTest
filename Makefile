objects = constTest.o

constTest:$(objects)
	clang  -o constTest $(objects) && ./constTest

constTest.o : constTest.c

.PHONY : clean

clean:
	-rm constTest $(objects)
