//
// COMP1511 lab02 - Word Addition
//
// By Soorriamoorthy S Saruva
//

#include <stdio.h>

int main(void) {
    int num1;
    int num2;
    int sum;

    printf("Please enter two integers: ");
    scanf("%d%d", &num1, &num2);

    sum = num1 + num2;

    // Print the first number
    if (num1 < 0) {
        num1 = -num1;
        printf("negative ");
    }

    if (num1 == 0) {
        printf("zero");
    } else if (num1 == 1) {
        printf("one");
    } else if (num1 == 2) {
        printf("two");
    } else if (num1 == 3) {
        printf("three");
    } else if (num1 == 4) {
        printf("four");
    } else if (num1 == 5) {
        printf("five");
    } else if (num1 == 6) {
        printf("six");
    } else if (num1 == 7) {
        printf("seven");
    } else if (num1 == 8) {
        printf("eight");
    } else if (num1 == 9) {
        printf("nine");
    } else if (num1 == 10) {
        printf("ten");
    } else {
        printf("%d", num1);
    }

    printf(" + ");

    // Print the second number
    if (num2 < 0) {
        num2 = -num2;
        printf("negative ");
    }

    if (num2 == 0) {
        printf("zero");
    } else if (num2 == 1) {
        printf("one");
    } else if (num2 == 2) {
        printf("two");
    } else if (num2 == 3) {
        printf("three");
    } else if (num2 == 4) {
        printf("four");
    } else if (num2 == 5) {
        printf("five");
    } else if (num2 == 6) {
        printf("six");
    } else if (num2 == 7) {
        printf("seven");
    } else if (num2 == 8) {
        printf("eight");
    } else if (num2 == 9) {
        printf("nine");
    } else if (num2 == 10) {
        printf("ten");
    } else {
        printf("%d", num2);
    }

    printf(" = ");

    if (sum < 0) {
        printf("negative");
    }

    if (sum == 0) {
        printf("zero");
    } else if (sum == 1 || sum == -1) {
        printf("one");
    } else if (sum == 2 || sum == -2) {
        printf("two");
    } else if (sum == 3 || sum == -3) {
        printf("three");
    } else if (sum == 4 || sum == -4) {
        printf("four");
    } else if (sum == 5 || sum == -5) {
        printf("five");
    } else if (sum == 6 || sum == -6) {
        printf("six");
    } else if (sum == 7 || sum == -7) {
        printf("seven");
    } else if (sum == 8 || sum == -8) {
        printf("eight");
    } else if (sum == 9 || sum == -9) {
        printf("nine");
    } else if (sum == 10 || sum == -10) {
        printf("ten");
    } else {
        printf("%d", sum);
    }

    printf("\n");

    return 0;
}
