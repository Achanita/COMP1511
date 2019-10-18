// 
// COMP1511 Week 4 Weekly Test - Print The Middle Integer of 3 Integers
// 
// By Soorriamoorthy Saruva (z5258068)
// 

#include <stdio.h>

int main(void) {
    int num1;
    int num2;
    int num3;

    // Get integers from user
    printf("Enter integer: ");
    scanf("%d", &num1);
    printf("Enter integer: ");
    scanf("%d", &num2);
    printf("Enter integer: ");
    scanf("%d", &num3);

    if ((num1 >= num2 && num1 <= num3) 
        || (num1 >= num3 && num1 <= num2)) {
        printf("Middle: %d\n", num1);
    } else if ((num2 >= num3 && num2 <= num1) 
        || (num2 >= num1 && num2 <= num3)) {
        printf("Middle: %d\n", num2);
    } else {
        printf("Middle: %d\n", num3);
    }


    return 0;
}