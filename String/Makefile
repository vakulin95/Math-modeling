CFLAGS = -c -Wall
LFLAGS = -lm -o

all: built

built: main.o func.o
	gcc $^ $(LFLAGS) main.out

%.o: %.c
	gcc $(CFLAGS) $<

clean :
	rm -rf *.o *.out files/*.txt
