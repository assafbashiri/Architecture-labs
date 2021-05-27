#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: count-words

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: count-words.o
	gcc -m32 -g -Wall -o count-words count-words.o

# Depends on the source and header files
encoder.o: count-words.c
	gcc -m32 -g -Wall -c -o count-words.o count-words.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o count-words 
