#format is target-name: target dependencies
#{-tab-}actions

# All Targets
#all: task0

# Tool invocations
# Executable "encoder" depends on the files encoder.o
compile:
	nasm -f elf32 start.s -o start.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

# Depends on the source and header files


	ld -m elf_i386 start.o main.o util.o -o flame2
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o flame2
