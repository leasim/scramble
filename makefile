all: scramble

scramble: main.o
	gcc main.o -o scramble

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *o scramble
