//
// COMP1511 Lab03 - Three or Five
//
// By Soorriamoorthy Saruva (z5258068)
//

#define or ||

#include <stdio.h>

int main(void) {
    int max;

    printf("Enter number: ");
    scanf("%d", &max);

    int counter = 3;

    while (counter < max) {
        if (counter % 3 == 0 or counter % 5 == 0) {
            printf("%d\n", counter);
        }
        counter++;
    }

    return 0;
}