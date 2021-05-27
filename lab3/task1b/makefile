#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: virus1b

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: virus1b.o
	gcc -m32 -g -Wall -o virus1b virus1b.o

# Depends on the source and header files
encoder.o: virus1b.c
	gcc -m32 -g -Wall -c -o virus1b.o virus1b.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o virus 1b
