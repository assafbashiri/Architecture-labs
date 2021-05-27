#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int NumberOfdigits(char* input) {
    int i=0;
    int numberOfDigits = 0;
    while(input[i])
    {
        if((input[i] >= 48) && (input[i] <= 57))
            numberOfDigits++;
        i++;
    }
    return numberOfDigits;
}

int main(int argc, char* argv[]) {
    if(argc > 1) 
        printf("The number of digits in the string is: %d\n", NumberOfdigits(argv[1]));

    return 0;
}
