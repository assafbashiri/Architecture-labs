#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: hexaPrint

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: hexaPrint.o
	gcc -m32 -g -Wall -o hexaPrint hexaPrint.o

# Depends on the source and header files
encoder.o: hexaPrint.c
	gcc -m32 -g -Wall -c -o hexaPrint.o hexaPrint.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o hexaPrint 
