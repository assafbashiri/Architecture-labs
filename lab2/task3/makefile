#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: menu_map

# Tool invocations
# Executable "encoder" depends on the files encoder.o
encoder: menu_map.o
	gcc -m32 -g -Wall -o menu_map menu_map.o

# Depends on the source and header files
encoder.o: menu_map.c
	gcc -m32 -g -Wall -c -o menu_map.o menu_map.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o menu_map 
