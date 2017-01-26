CFLAGS = -c -Wall
LFLAGS = -lm -o

all: built run clean plot

built: main.o
	@gcc main.o $(LFLAGS) main.out

main.o: main.c
	@gcc $(CFLAGS) main.c

run:
	@./main.out

plot:
	@gnuplot "anim_pl_phase.gnu"

clean:
	@rm -rf *.out *.o
