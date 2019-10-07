//
// COMP1511 Lab03 - Countdown
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int counter = 10;

    while (counter >= 0) {
        printf("%d\n", counter);

        counter -= 1;
    }

    return 0;
}