#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: virus

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: virus.o
	gcc -m32 -g -Wall -o virus virus.o

# Depends on the source and header files
encoder.o: virus.c
	gcc -m32 -g -Wall -c -o virus.o virus.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o virus 
