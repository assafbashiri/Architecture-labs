#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: virus2a

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: virus2a.o
	gcc -m32 -g -Wall -o virus2a virus2a.o

# Depends on the source and header files
encoder.o: virus2a.c
	gcc -m32 -g -Wall -c -o virus2a.o virus2a.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o virus2a
