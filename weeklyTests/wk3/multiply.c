//
// COMP1511 Week 3 Weekly Test - Print the Absolute Multiple of Two Integers
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int num1;
    int num2;

    // Get the two numbers
    scanf("%d%d", &num1, &num2);

    // Account for negative inputs
    if (num1 < 0) {
        num1 = -num1;
    }
    if (num2 < 0) {
        num2 = -num2;
    }

    int product = num1 * num2;

    // Check if the product is zero
    if (product == 0) {
        printf("zero\n");
    } else {
        printf("%d\n", product);
    }

    return 0;
}