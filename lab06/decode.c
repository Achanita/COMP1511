//
// COMP1511 lab06 - Decrypting a Substitution Cipher
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

#define NUM_ALPHA 26

int decode(int character, int map[NUM_ALPHA]);

int main(void) {
    int map[NUM_ALPHA];
    int i = 0;

    while (i < NUM_ALPHA) {
        map[getchar() - 'a'] = i;
        i++;
    }
    getchar();
    int character = getchar();
    while (character != EOF) {
        putchar(decode(character, map));
        character = getchar();
    }
    return 0;
}

int decode(int character, int map[NUM_ALPHA]) {
    if (character >= 'a' && character <= 'z') {
        int characterPosition = character - 'a';
        return 'a' + map[characterPosition];
    } else if (character >= 'A' && character <= 'Z') {
        int characterPosition = character - 'A';
        return 'A' + map[characterPosition];
    }
    return character;
}