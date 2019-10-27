//
// COMP1511 lab06 - Devowelling Text
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int is_vowel(int character);

int main(void) {
    int character = getchar();
    while (character != EOF) {
        if (!is_vowel(character)) {
            putchar(character);
        }
        character = getchar();
    }

    return 0;
}

int is_vowel(int character) {
    if (character == 'a' || character == 'e' ||
        character == 'i' || character == 'o' ||
        character == 'u') {
        return 1;
    }
    return 0;
}