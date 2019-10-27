//
// COMP1511 lab06 - Encrypting Text with a Caesar Cipher
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int encrypt(int character, int shiftAmount);

int main(void) {
    int shiftAmount = 0;
    scanf("%d", &shiftAmount);
    int character = getchar();
    while (character != EOF) {
        putchar(encrypt(character, shiftAmount));
        character = getchar();
    }
    return 0;
}

int encrypt(int character, int shiftAmount) {
    shiftAmount = shiftAmount % 26;
    if (shiftAmount < 0) {
        shiftAmount += 26;
    }
    if (character >= 'a' && character <= 'z') {
        int characterPosition = character - 'a';
        int newPosition = (characterPosition + shiftAmount) % 26;
        return 'a' + newPosition;
    } else if (character >= 'A' && character <= 'Z') {
        int characterPosition = character - 'A';
        int newPosition = (characterPosition + shiftAmount) % 26;
        return 'A' + newPosition;
    }
    return character;
}
