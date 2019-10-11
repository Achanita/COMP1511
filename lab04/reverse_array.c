//
// COMP1511 Lab04 - Reverse an Array
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>
#define SIZE 100

int main(void) {

    int numbers[SIZE] = {0};

    printf("Enter numbers forwards:\n");
    int i = 0;
    while ((i < SIZE) && (scanf("%d", &numbers[i]) == 1)) {
        i++;
    }

    printf("Reversed:\n");
    while (i > 0) {
        i--;
        printf("%d\n", numbers[i]);
    }

    return 0;
}