//
// COMP1511 Week 3 Weekly Test - Print The Direction of Three Numbers 
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    double num1;
    double num2;
    double num3;

    // Get the three numbers
    printf("Please enter three numbers: ");\
    scanf("%lf%lf%lf", &num1, &num2, &num3);

    if (num1 > num2 && num2 > num3) {
        printf("down\n");
    } else if (num1 < num2 && num2 < num3) {
        printf("up\n");
    } else {
        printf("neither\n");
    }

    return 0;
}