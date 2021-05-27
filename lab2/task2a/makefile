#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: array

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: array.o
	gcc -m32 -g -Wall -o array array.o

# Depends on the source and header files
encoder.o: array.c
	gcc -m32 -g -Wall -c -o array.o array.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o array 
