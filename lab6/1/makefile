all: mypipe
mypipe: task1.c
	gcc -g -m32 -c -o task1.o task1.c
	gcc -g -m32 -c -o LineParser.o LineParser.c
	

	gcc -g -m32  task1.o LineParser.o -o mypipe
	

.PHONY: clean
clean:
	rm -rf ./*.o mypipe
