CFLAGS = -c -Wall -I/usr/local/include
GSLFLAGS = -L/usr/local/lib
LFLAGS = -lm

all: built run clean plot

built: main.o
	@gcc $(GSLFLAGS) main.o $(LFLAGS)

main.o: main.c
	@gcc $(CFLAGS) main.c

run:
	@./a.out

plot:
	@gnuplot "plot.gnu"	
	@rm files/*.dat

clean:
	@rm -rf *.out *.o
