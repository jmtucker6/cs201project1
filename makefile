objects = value.o node.o stack.o queue.o scanner.o fatal.o equationConverter.o \
		  calculon.o bst.o processEquation.o
executables = calculon test/valueTest test/bstTest

calculon : $(objects)
	gcc -Wall -std=c99 -g $(objects) -o calculon -lm
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
fatal.o : fatal.c fatal.h 
	gcc -Wall -std=c99 -g -c fatal.c
equationConverter.o : equationConverter.c equationConverter.h stack.h queue.h
	gcc -Wall -std=c99 -g -c equationConverter.c
bst.o : bst.c bst.h fatal.h value.h
	gcc -Wall -std=c99 -g -c bst.c
calculon.o : calculon.c stack.h queue.h value.h scanner.h equationConverter.h
	gcc -Wall -std=c99 -g -c calculon.c
processEquation.o : processEquation.h processEquation.c value.h queue.h stack.h
	gcc -Wall -std=c99 -g -c processEquation.c -lm
valueTest : value.o scanner.o value.h scanner.h
	gcc -Wall -std=c99 -g test/valueTest.c scanner.o value.o -o test/valueTest
bstTest : value.o value.h bst.o bst.h
	gcc -Wall -std=c99 -g test/bstTest.c value.o bst.o -o test/bstTest
test : calculon bstTest
	test/bstTest
	./calculon test/testFile
	./calculon -v
	./calculon test/crazyTest1
	./calculon test/crazyTest2
	./calculon test/crazyTest3
	@echo "Testing complete!"
clean:
	rm -f $(objects) $(executables)
