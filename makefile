all:
	gcc -Wall -c value.c
	gcc -Wall -c stack.c
clean:
	rm value.o stack.o
