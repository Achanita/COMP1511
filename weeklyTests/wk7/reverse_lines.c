//
// COMP1511 Week 7 Weekly Test - Printing Lines Reversed
//
// By Soorriamoorthy Saruva (z525806) on 1-11-19
//

#include <stdio.h>

#define MAX_STR_LENGTH 256

int main(void) {
    char input[MAX_STR_LENGTH];

    while (fgets(input, MAX_STR_LENGTH, stdin) != NULL) {
        // Get the string's length
        int length = 0;
        while (input[length] != '\0' && input[length] != '\n') {
            length++;
        }
        // Iterate through the string backwards
        int i = length - 1;
        while (i >= 0) {
            putchar(input[i]);
            i--;
        }
        printf("\n");
    }

    return 0;
}