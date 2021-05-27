#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: main

# Tool invocations
# Executable "encoder" depends on the files encoder.o
main: main.o
	gcc -m32 -g -Wall -o exc main.o

# Depends on the source and header files
main.o: main.c
	gcc -g -Wall -m32  -c -o main.o main.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o exc 
