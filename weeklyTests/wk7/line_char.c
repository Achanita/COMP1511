//
// COMP1511 Week 7 Weekly Test - Line Character
//
// By Soorriamoorthy Saruva (z525806) on 1-11-19
//

#include <stdio.h>

#define MAX_STR_LENGTH 256

int main(void) {
    // Get the input string
    char string[MAX_STR_LENGTH];
    fgets(string, MAX_STR_LENGTH, stdin);

    // Get the index of the input string required
    int index;
    scanf("%d", &index);

    // Get the result character from the input string
    int result = string[index];
    printf("The character in position %d is '%c'\n", index, result);

    return 0;
}