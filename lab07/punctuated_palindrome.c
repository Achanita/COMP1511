//
// COMP1511 lab07 - Is it a Palindrome?
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

#define MAX_LENGTH 4096

int main(void) {
    char input[MAX_LENGTH];
    char cleanStr[MAX_LENGTH];
    int isPalindrome = 1;

    printf("Enter a string: ");
    fgets(input, MAX_LENGTH, stdin);

    int length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        length++;
    }

    int left = 0;
    int right = length - 1;
    while (left <= right) {
        isPalindrome = isPalindrome && input[left] == input[right];

        left++;
        right--;
    }

    printf("String is ");
    if (!isPalindrome) {
        printf("not ");
    }
    printf("a palindrome\n");

    return 0;
}