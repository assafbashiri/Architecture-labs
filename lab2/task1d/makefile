#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: arrays

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: arrays.o
	gcc -m32 -g -Wall -o arrays arrays.o

# Depends on the source and header files
encoder.o: arrays.c
	gcc -m32 -g -Wall -c -o arrays.o arrays.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o arrays 
