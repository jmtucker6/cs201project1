objects = value.o node.o stack.o queue.o scanner.o fatal.o calculon.o

calculon : $(objects)
	gcc -Wall -std=c99 $(objects) -o calculon
value.o : value.c value.h
	gcc -Wall -std=c99 -g -c value.c
node.o : node.c node.h
	gcc -Wall -std=c99 -g -c node.c
stack.o : stack.c stack.h
	gcc -Wall -std=c99 -g -c stack.c
queue.o : queue.c queue.h
	gcc -Wall -std=c99 -g -c queue.c
scanner.o : scanner.c scanner.h
	gcc -Wall -std=c99 -g -c scanner.c
fatal.o : fatal.c fatal.h
	gcc -Wall -std=c99 -g -c fatal.c
calculon.o : calculon.c
	gcc -Wall -std=c99 -g -c calculon.c
clean:
	rm *.o calculon
