all: task
task: task0.c
	gcc -m32 -g -Wall -c -o task0.o task0.c
	#gcc -g -m32 -c -o LineParser.o LineParser.c
	

	gcc -m32 -g -Wall  task0.o  -o task
	

.PHONY: clean
clean:
	rm -rf ./*.o task
