CFLAGS = -c -Wall
LFLAGS = -lm -o

all: built run plot

built: main.o
	gcc main.o $(LFLAGS) main.out

main.o: main.c
	gcc $(CFLAGS) main.c

run:
	./main.out

plot:
	gnuplot "plot.gnu"

clean:
	rm -rf *.out *.o
