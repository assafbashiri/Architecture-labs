all: mypipe
mypipe: task0a.c
	gcc -g -m32 -c -o task0a.o task0a.c
	gcc -g -m32 -c -o LineParser.o LineParser.c
	

	gcc -g -m32  task0a.o LineParser.o -o mypipe
	

.PHONY: clean
clean:
	rm -rf ./*.o mypipe
