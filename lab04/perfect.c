//
// COMP1511 Lab04 - Are You Perfect?
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int number;

    printf("Enter number: ");
    scanf("%d", &number);

    int current = 1;
    int sumOfFactors = 0;
    printf("The factors of %d are:\n", number);
    while (current <= number) {
        if (number % current == 0) {
            printf("%d\n", current);
            sumOfFactors += current;
        }

        
        current++;
    }

    printf("Sum of factors = %d\n", sumOfFactors);
    if (sumOfFactors / 2 == number) {
        printf("%d is a perfect number\n", number);
    } else {
        printf("%d is not a perfect number\n", number);
    }

    return 0;
}