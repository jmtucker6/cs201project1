objects = value.o node.o stack.o queue.o scanner.o fatal.o equationConverter.o calculon.o 
executables = calculon test/valueTest

calculon : $(objects)
	gcc -Wall -std=c99 -g $(objects) -o calculon
value.o : value.c value.h
	gcc -Wall -std=c99 -g -c value.c
node.o : node.c node.h fatal.h value.h
	gcc -Wall -std=c99 -g -c node.c
stack.o : stack.c stack.h node.h value.h
	gcc -Wall -std=c99 -g -c stack.c
queue.o : queue.c queue.h node.h value.h fatal.h
	gcc -Wall -std=c99 -g -c queue.c
scanner.o : scanner.c scanner.h
	gcc -Wall -std=c99 -g -c scanner.c
fatal.o : fatal.c fatal.h scanner.h
	gcc -Wall -std=c99 -g -c fatal.c
equationConverter.o : equationConverter.h stack.h queue.h
	gcc -Wall -std=c99 -g -c equationConverter.c
calculon.o : calculon.c stack.h queue.h value.h scanner.h equationConverter.h
	gcc -Wall -std=c99 -g -c calculon.c
valueTest : value.o scanner.o value.h scanner.h
	gcc -Wall -std=c99 -g test/valueTest.c scanner.o value.o -o test/valueTest
clean:
	rm -f $(objects) $(executables)
