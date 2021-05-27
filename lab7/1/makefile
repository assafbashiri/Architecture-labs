all: task
task: task0.c
	gcc -g -m32 -c -o task0.o task0.c
	#gcc -g -m32 -c -o LineParser.o LineParser.c
	

	gcc -g -m32  task0.o  -o task
	

.PHONY: clean
clean:
	rm -rf ./*.o task
