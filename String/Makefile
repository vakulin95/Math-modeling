#Makefile

CFLAGS = -c -Wall -O3
LFLAGS = -lm -o

all: built run plot clean

run:
	@./main.out

built: main.o func.o
	@gcc $^ $(LFLAGS) main.out

%.o: %.c
	@gcc $(CFLAGS) $<

plot:
	@echo Plotting out.gif
	@gnuplot "plot.gnu"

clean :
	@rm -rf *.o *.out files/*.dat
