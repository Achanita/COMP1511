//
// COMP1511 Lab03 - Ordering Three Integers
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int num1;
    int num2;
    int num3;

    int min;
    int middle;
    int max;

    // Get the three numbers
    printf("Enter integer: ");
    scanf("%d", &num1);
    printf("Enter integer: ");
    scanf("%d", &num2);
    printf("Enter integer: ");
    scanf("%d", &num3);

    if (num1 >= num2 && num1 >= num3) {
        max = num1;
        if (num2 > num3) {
            middle = num2;
            min = num3;
        } else {
            middle = num3;
            min = num2;
        }
    } else if (num2 >= num1 && num2 >= num3) {
        max = num2;
        if (num1 > num3) {
            middle = num1;
            min = num3;
        } else {
            middle = num3;
            min = num1;
        }
    } else {
        max = num3;
        if (num1 > num2) {
            middle = num1;
            min = num2;
        } else {
            middle = num2;
            min = num1;
        }
    }

    printf("The integers in order are: %d %d %d\n", min, middle, max);
    
    return 0;
}