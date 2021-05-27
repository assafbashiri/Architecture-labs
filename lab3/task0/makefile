#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: bubblesort

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: bubblesort.o
	gcc -m32 -g -Wall -o bubblesort bubblesort.o

# Depends on the source and header files
encoder.o: bubblesort.c
	gcc -m32 -g -Wall -c -o bubblesort.o bubblesort.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o bubblesort 
