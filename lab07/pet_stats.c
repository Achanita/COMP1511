//
// COMP1511 lab07 - Pet Statistics
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 50

struct pet {
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int age;
    int weight;
};

// function declarations, do not change these
void setup_pet(
    struct pet *my_pet,
    char *name,
    char *type,
    char *age,
    char *weight);
void print_pet(struct pet *my_pet);

// do not change any code in the main function
int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("%s should receive four extra command line arguments.\n", argv[0]);
        return 1;
    }
    struct pet new_pet;
    setup_pet(&new_pet, argv[1], argv[2], argv[3], argv[4]);
    print_pet(&new_pet);
    return 0;
}

// A function that reads two lines then two
// ints from standard input, storing them
// in the pet struct
void setup_pet(
    struct pet *my_pet,
    char *name,
    char *type,
    char *age,
    char *weight) {
    strcpy(my_pet->name, name);
    strcpy(my_pet->type, type);
    my_pet->age = strtol(age, NULL, 10);
    my_pet->weight = strtol(weight, NULL, 10);
}

// a function that prints out a human readable
// description of the pet:
// "<name> is a <type> that is <age> years old and weighs <weight>kg\n"
void print_pet(struct pet *my_pet) {
    printf("%s is a %s who is %d years old and weighs %dkg\n",
           my_pet->name,
           my_pet->type,
           my_pet->age,
           my_pet->weight);
}
