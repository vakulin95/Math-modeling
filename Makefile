CFLAGS = -c -Wall -I/usr/local/include
GSLFLAGS = -L/usr/local/lib
LFLAGS = -lgsl -lgslcblas -lm

all: built run clean

built: main.o
	gcc $(GSLFLAGS) main.o $(LFLAGS)

main.o: main.c
	gcc $(CFLAGS) main.c

run:
	./a.out

clean:
	@rm -rf *.out *.o
