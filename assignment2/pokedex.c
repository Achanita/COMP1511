// Assignment 2 19T3 COMP1511: Pokedex
// pokedex.c
//
// This program was written by Soorriamoorthy S Saruva (z5258068)
// on 24-11-19
//
// Version 3.5.2: Add comments

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Note you are not allowed to use <string.h> in this assignment
// There are some techniques we would like you to learn to code
// that the string library trivialises.

// ----------------------------------------------
// Add any extra #includes your code needs here.
// ----------------------------------------------

#include "pokedex.h"

// ----------------------------------------------
// Add your own #defines here.
// ----------------------------------------------

enum error_type {
    NEW_POKEMON_SAME_ID,
    NO_CURRENT_POKEMON,
    EMPTY_POKEDEX,
    EVOLUTION_SAME_ID,
    EVOLUTION_NO_FROM_POKEMON,
    EVOLUTION_NO_TO_POKEMON,
};

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.
struct pokedex {
    struct pokenode *head;
    struct pokenode *selected_node;
};

// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
//
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.
struct pokenode {
    Pokemon pokemon;
    struct pokenode *next;
    struct pokenode *prev;
    struct pokenode *evolution;
    int found;
};

// ----------------------------------------------
// Add your own structs here.
// ----------------------------------------------

// ----------------------------------------------
// Add prototypes for your own functions here.
// ----------------------------------------------

static void print_pokemon_name(Pokemon pokemon, int found);

static void destroy_pokenode(struct pokenode *node);

static int str_length(char *string);

static void print_pokemon_types(Pokemon pokemon, char *separator);

static int pokemon_has_type(Pokemon pokemon, pokemon_type type);

static void find_all_pokemon(Pokedex pokedex);

static Pokemon copy_pokemon(Pokemon pokemon);

static void add_pokemon_sorted(Pokedex pokedex, Pokemon pokemon);

static int str_contains(char *string, char *substring);

static int str_equals(char *string1, char *string2);

static char toLower(char ch);

static void handle_error(enum error_type error);

// Creates a new pokenode struct and returns a pointer to it.
static struct pokenode *new_pokenode(Pokemon pokemon);

// You need to implement the following functions in their stages.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h

// Creates a new Pokedex, and returns a pointer to it.
// Note: you will need to modify this function.
Pokedex new_pokedex(void) {
    // Malloc memory for a new Pokedex, and check that the memory
    // allocation succeeded.
    Pokedex pokedex = malloc(sizeof(struct pokedex));
    assert(pokedex != NULL);

    // Set the head of the linked list to be NULL.
    // (i.e. set the Pokedex to be empty)
    pokedex->head = NULL;
    pokedex->selected_node = NULL;

    return pokedex;
}

// Create a new pokenode struct and returns a pointer to it.
//
// This function should allocate memory for a pokenode, set its pokemon
// pointer to point to the specified pokemon, and return a pointer to
// the allocated memory.
static struct pokenode *new_pokenode(Pokemon pokemon) {
    struct pokenode *new = malloc(sizeof(struct pokenode));
    new->pokemon = pokemon;
    // Set found and next to default values
    new->found = 0;
    new->next = NULL;
    new->prev = NULL;
    new->evolution = NULL;

    return new;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add a new Pokemon to the Pokedex.
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    if (pokedex->head == NULL) {
        // If the pokedex is empty, set the head and selected node to the
        // new pokenode
        struct pokenode *new = new_pokenode(pokemon);
        pokedex->head = new;
        pokedex->selected_node = new;
    } else {
        // Otherwise insert the new pokenode at the end of the pokedex
        struct pokenode *current = pokedex->head;
        int id_is_unique = 1;
        int id = pokemon_id(pokemon);

        if (pokemon_id(current->pokemon) == id) {
            id_is_unique = 0;
        }
        
        // Iterate through the linked list while the pokemon_id is unique and
        // the current Pokenode points to a next Pokenode.
        while (id_is_unique && current->next != NULL) {
            if (pokemon_id(current->pokemon) == id) {
                id_is_unique = 0;
            }
            current = current->next;
        }
        if (id_is_unique) {
            // Only create and add the new pokemon if its `pokemon_id` is unique
            struct pokenode *new = new_pokenode(pokemon);
            new->prev = current;
            current->next = new;
        } else {
            // Otherwise print out error message and exit
            handle_error(NEW_POKEMON_SAME_ID);
        }
    }
}

// Print out the details of the currently selected Pokemon.
void detail_pokemon(Pokedex pokedex) {
    struct pokenode *selected_node = pokedex->selected_node;
    if (selected_node != NULL) {
        Pokemon selected = selected_node->pokemon;
        int found = selected_node->found;

        // Print out all the details
        printf("ID: %03d\n", pokemon_id(selected));
        printf("Name: ");
        print_pokemon_name(selected, found);
        printf("\n");
        if (found) {
            // If the pokemon has been found, print information
            printf("Height: %.1lfm\n", pokemon_height(selected));
            printf("Weight: %.1lfkg\n", pokemon_weight(selected));

            printf("Type: ");
            print_pokemon_types(selected, " ");
            printf("\n");
        } else {
            // If the pokemon has not been found, print placeholders
            printf("Height: --\n");
            printf("Weight: --\n");
            printf("Type: --\n");
        }
    }
}

// Return the currently selected Pokemon.
Pokemon get_current_pokemon(Pokedex pokedex) {
    if (pokedex->selected_node == NULL) {
        handle_error(NO_CURRENT_POKEMON);
    }
    return pokedex->selected_node->pokemon;
}

// Sets the currently selected Pokemon to be 'found'.
void find_current_pokemon(Pokedex pokedex) {
    struct pokenode *selected_node = pokedex->selected_node;
    // If the selected node exists, set its Pokemon to be found.
    if (selected_node != NULL) {
        selected_node->found = 1;
    }
}

// Print out all of the Pokemon in the Pokedex.
void print_pokemon(Pokedex pokedex) {
    struct pokenode *current = pokedex->head;
    struct pokenode *selected = pokedex->selected_node;
    // Iterate through the Pokedex, printing each one's id and name.
    while (current != NULL) {
        if (current == selected) {
            // If the Pokemon is currently selected, print an arrow to show this.
            printf("--> ");
        } else {
            // Otherwise print spaces.
            printf("    ");
        }

        int id = pokemon_id(current->pokemon);
        printf("#%03d: ", id);

        print_pokemon_name(current->pokemon, current->found);
        printf("\n");

        current = current->next;
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                        //
//////////////////////////////////////////////////////////////////////

// Change the currently selected Pokemon to be the next Pokemon in the Pokedex.
void next_pokemon(Pokedex pokedex) {
    struct pokenode *selected = pokedex->selected_node;
    // Only set the next pokemon if the current Pokemon exists and the next 
    // Pokemon exists.
    if (selected != NULL && selected->next != NULL) {
        pokedex->selected_node = selected->next;
    }
}

// Change the currently selected Pokemon to be the previous Pokemon in the 
// Pokedex.
void prev_pokemon(Pokedex pokedex) {
    struct pokenode *selected = pokedex->selected_node;
    // Only set the next pokemon if the current Pokemon exists and the previous 
    // Pokemon exists.
    if (selected != NULL && selected->prev != NULL) {
        pokedex->selected_node = selected->prev;
    }
}

// Change the currently selected Pokemon to be the Pokemon with the ID `id`.
void change_current_pokemon(Pokedex pokedex, int id) {
    struct pokenode *current = pokedex->head;
    // Iterate through the linked list until the ID `id` equals the current
    // Pokemon's ID or the loop has reached the end of the linked list.
    while (current != NULL && pokemon_id(current->pokemon) != id) {
        current = current->next;
    }
    // If `current` is not `NULL`, then `current` is a value in the linked
    // list so the selected Pokemon can be changed.
    if (current != NULL) {
        pokedex->selected_node = current;
    }
}

// Remove the currently selected Pokemon from the Pokedex.
void remove_pokemon(Pokedex pokedex) {
    struct pokenode *remNode = pokedex->selected_node;
    // If `remNode` is NULL, then the pokedex is empty
    if (remNode != NULL) {
        if (remNode == pokedex->head) {
            // If the selected node is the head, set the next pokemon to be 
            // the head
            pokedex->selected_node = remNode->next;
            pokedex->head = remNode->next;
        } else {
            struct pokenode *next = remNode->next;
            struct pokenode *prev = remNode->prev;

            // Remove the node from the list in the forward direction
            prev->next = next;

            if (next == NULL) {
                // If the pokemon is the last one in the list
                // set selected to the previous node
                pokedex->selected_node = prev;
            } else {
                // Otherwise set select to the next node.
                next->prev = prev;
                pokedex->selected_node = next;
            }
        }

        destroy_pokenode(remNode);
    }
}

// Destroy the given Pokedex and free all associated memory.
void destroy_pokedex(Pokedex pokedex) {
    struct pokenode *current = pokedex->head;
    // Iterate through the Pokedex, deleting each Pokenode
    while (current != NULL) {
        struct pokenode *next = current->next;
        destroy_pokenode(current);
        current = next;
    }
    free(pokedex);
}

//////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                        //
//////////////////////////////////////////////////////////////////////

// Print out all of the different types of Pokemon in the Pokedex.
void show_types(Pokedex pokedex) {
    // Array to hold whether a type has been printed already
    int type_printed_map[MAX_TYPE - 1] = {0};
    struct pokenode *current = pokedex->head;
    // Iterate through the Pokedex, printing all the types
    while (current != NULL) {
        Pokemon current_pokemon = current->pokemon;
        
        // Print `first_type` if it has not been printed already
        pokemon_type first_type = pokemon_first_type(current_pokemon);
        if (!type_printed_map[first_type]) {
            type_printed_map[first_type] = 1;
            printf("%s\n", pokemon_type_to_string(first_type));
        }

        // Print `second_type` if it has not been printed already
        // and it is not NONE_TYPE
        pokemon_type second_type = pokemon_second_type(current_pokemon);
        if (!type_printed_map[second_type] && second_type != NONE_TYPE) {
            type_printed_map[second_type] = 1;
            printf("%s\n", pokemon_type_to_string(second_type));
        }
        current = current->next;
    }
}

// Set the first not-yet-found Pokemon of each type to be found.
// If a Pokemon is found and has two types, new Pokemon with either type will
// not be found.
void go_exploring(Pokedex pokedex) {
    // Array to hold whether a type has been set to be found already
    int type_found_map[MAX_TYPE - 1] = {0};
    struct pokenode *current = pokedex->head;
    while (current != NULL) {
        // Only set the Pokemon to be found if it has not already been found
        if (!current->found) {
            Pokemon current_pokemon = current->pokemon;

            // Set the pokemon to be found if a pokemon of its first type has
            // not been found
            pokemon_type first_type = pokemon_first_type(current_pokemon);
            if (!type_found_map[first_type]) {
                type_found_map[first_type] = 1;
                current->found = 1;
            }

            // Set the pokemon to be found if its second type is not none 
            // and a pokemon of its second type has not been found.
            pokemon_type second_type = pokemon_second_type(current_pokemon);
            if (second_type != NONE_TYPE && !type_found_map[second_type]) {
                type_found_map[second_type] = 1;
                current->found = 1;
            }
        }
        current = current->next;
    }
}

// Return the total number of Pokemon in the Pokedex.
int count_total_pokemon(Pokedex pokedex) {
    struct pokenode *current = pokedex->head;
    int count = 0;
    // while the current pokenode if not NULL, increment the count
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Return the number of Pokemon in the Pokedex that have been found.
int count_found_pokemon(Pokedex pokedex) {
    struct pokenode *current = pokedex->head;
    int count = 0;
    // While the current pokenode if not NULL, increment the count if the 
    // Pokemon has not been found.
    while (current != NULL) {
        if (current->found) {
            count++;
        }                         ////////////
        current = current->next;  ////////////////////
    }
    return count;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add the information that the Pokemon with the ID `from_id` can
// evolve into the Pokemon with the ID `to_id`.
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    // Check if `from_id` and `to_id` are the same and exit if 
    // they are.
    if (from_id == to_id) {
        handle_error(EVOLUTION_SAME_ID);
    }

    struct pokenode *from_pokenode = NULL;
    struct pokenode *to_pokenode = NULL;
    struct pokenode *current = pokedex->head;

    // Iterate through the Pokedex while there are more Pokemon or 
    // either of from_pokenode and to_pokenode have not been found
    while (current != NULL || (from_pokenode == NULL && to_pokenode == NULL)) {
        int id = pokemon_id(current->pokemon);
        if (from_id == id) {
            from_pokenode = current;
        } else if (to_id == id) {
            to_pokenode = current;
        }
        current = current->next;
    }

    if (from_pokenode == NULL) {
        handle_error(EVOLUTION_NO_FROM_POKEMON);
    } else if (to_pokenode == NULL) {
        handle_error(EVOLUTION_NO_TO_POKEMON);
    } else {
        from_pokenode->evolution = to_pokenode;
    }
}

// Show the evolutions of the currently selected Pokemon.
void show_evolutions(Pokedex pokedex) {
    struct pokenode *current = pokedex->selected_node;
    // Iterate throught the selected Pokemon's evolutions.
    while (current != NULL && current->pokemon) {

        Pokemon current_pokemon = current->pokemon;
        int id = pokemon_id(current_pokemon);
        printf("#%03d ", id);

        if (current->found) {
            // If the pokemon has been found, print its name and type(s)
            print_pokemon_name(current_pokemon, 1);
            printf(" [");
            print_pokemon_types(current_pokemon, " ");
            printf("]");
        } else {
            // If the pokemon has not been found, print a placeholder
            printf("???? [????]");
        }

        // If there is an evolution, print an arrow
        if (current->evolution != NULL) {
            printf(" --> ");
        }

        current = current->evolution;
    }
    printf("\n");
}

// Return the pokemon_id of the Pokemon that the currently selected
// Pokemon evolves into.
int get_next_evolution(Pokedex pokedex) {
    // If there is no current Pokemon, print an error and exit.
    if (pokedex->selected_node == NULL) {
        handle_error(EMPTY_POKEDEX);
    }
    struct pokenode *evolution = pokedex->selected_node->evolution;
    // If the current Pokemon has an evolution, return its evolution's
    // pokemon_id
    if (evolution != NULL) {
        return pokemon_id(evolution->pokemon);
    }
    // Otherwise return DOES_NOT_EVOLVE
    return DOES_NOT_EVOLVE;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                        //
//////////////////////////////////////////////////////////////////////

// Create a new Pokedex which contains only the Pokemon of a specified
// type from the original Pokedex.
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    Pokedex new = new_pokedex();
    struct pokenode *current = pokedex->head;

    while (current != NULL) {
        Pokemon current_pokemon = current->pokemon;
        // If the Pokemon has been found and has the given type,
        // add it to the new Pokedex
        if (current->found && pokemon_has_type(current_pokemon, type)) {
            add_pokemon(new, copy_pokemon(current_pokemon));
        }
        current = current->next;
    }

    // Set all the Pokemon in the new Pokedex to be found
    find_all_pokemon(new);

    return new;
}

// Create a new Pokedex which contains only the Pokemon that have
// previously been 'found' from the original Pokedex.
Pokedex get_found_pokemon(Pokedex pokedex) {
    Pokedex new = new_pokedex();
    struct pokenode *current = pokedex->head;

    while (current != NULL) {
        // If the Pokemon has been found, add it to the new Pokedex,
        // in the correct position so that pokemon_id of the Pokemon
        // are ascending.
        if (current->found) {
            add_pokemon_sorted(new, copy_pokemon(current->pokemon));
        }
        current = current->next;
    }

    // Set the currently selected Pokemon to be the first Pokemon in
    // the Pokedex
    new->selected_node = new->head;
    // Set all Pokemon in the new Pokedex to be found
    find_all_pokemon(new);

    return new;
}

// Create a new Pokedex containing only the Pokemon from the original
// Pokedex which have the given string appearing in its name.
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    Pokedex new = new_pokedex();
    struct pokenode *current = pokedex->head;

    while (current != NULL) {
        Pokemon current_pokemon = current->pokemon;
        char *name = pokemon_name(current_pokemon);
        // Add the Pokemon to the new pokedex if it has been found, 
        // and its name contains `text`
        if (current->found && str_contains(name, text)) {
            add_pokemon(new, copy_pokemon(current_pokemon));
        }
        current = current->next;
    }

    // Set all Pokemon in the new Pokedex to be found
    find_all_pokemon(new);

    return new;
}

//////////////////////////////////////////////////////////////////////
//                         Helper Functions                         //
//////////////////////////////////////////////////////////////////////

// Print the pokemon's name if it has been found. Otherwise print
// a placholder
static void print_pokemon_name(Pokemon pokemon, int found) {
    char *name = pokemon_name(pokemon);
    if (found) {
        // If the pokemon has been found, print its name.
        printf("%s", name);
    } else {
        // Get the name's length
        int name_length = str_length(name);
        // Print an asterisk for character in the Pokemon's name.
        int i = 0;
        while (i < name_length) {
            printf("*");
            i++;
        }
    }
}


// Destroys and frees a pokenode
static void destroy_pokenode(struct pokenode *node) {
    destroy_pokemon(node->pokemon);
    free(node);
}

// Returns the length of a string
static int str_length(char *string) {
    int length = 0;
    // While the current char is not the null terminator,
    // increment the length
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

// Print the given `pokemon`s type(s) with the given separator
// between them if the `pokemon` has a second type.
static void print_pokemon_types(Pokemon pokemon, char *separator) {
    // Print the Pokemon's first type
    pokemon_type first_type = pokemon_first_type(pokemon);
    printf("%s", pokemon_type_to_string(first_type));

    // If the Pokemon's second type is not NONE_TYPE, print the separator
    // and print the type.
    pokemon_type second_type = pokemon_second_type(pokemon);
    if (second_type != NONE_TYPE) {
        printf("%s", separator);
        printf("%s", pokemon_type_to_string(second_type));
    }
}

// Return whether the given pokemon has the given type as its
// first or second type.
static int pokemon_has_type(Pokemon pokemon, pokemon_type type) {
    // Check if the type is the first type
    pokemon_type first_type = pokemon_first_type(pokemon);
    if (first_type == type) {
        return 1;
    }

    // Only check if it is the second type, if it is not the 
    // first type
    pokemon_type second_type = pokemon_second_type(pokemon);
    if (second_type == type) {
        return 1;
    }

    return 0;
}

// Set all the pokemon in a given pokedex to be found
static void find_all_pokemon(Pokedex pokedex) {
    struct pokenode *current = pokedex->head;
    // Iterate through the Pokedex and set each Pokemon to be found
    while (current != NULL) {
        current->found = 1;
        current = current->next;
    }
}

// Return a copy of a given pokemon
static Pokemon copy_pokemon(Pokemon pokemon) {
    return new_pokemon(
        pokemon_id(pokemon),
        pokemon_name(pokemon),
        pokemon_height(pokemon),
        pokemon_weight(pokemon),
        pokemon_first_type(pokemon),
        pokemon_second_type(pokemon)
    );
}

// Add a pokemon to the given pokedex so that the pokedex is sorted by
// `pokemon_id`. 
//
// Note: Does not check whether a Pokemon's pokemon_id is unique
// as it it only intended to be used when filtering a Pokedex to create 
// a new one (e.g. get_found_pokemon)
static void add_pokemon_sorted(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *new = new_pokenode(pokemon);
    struct pokenode *head = pokedex->head;
    int id = pokemon_id(pokemon);
    if (head == NULL) {
        // If the pokedex is empty, set the head and selected node to 
        // the new Pokenode
        pokedex->head = new;
        pokedex->selected_node = new;
    } else if (id < pokemon_id(head->pokemon)) {
        // If the new Pokemon's pokemon_id is less than the head's 
        // pokemon_id, then the new Pokenode becomes the Pokedex's
        // head.
        new->next = head;
        head->prev = new;
        pokedex->head = new;
    } else {
        struct pokenode *current = pokedex->head;
        
        // Iterate through the Pokedex while the current Pokenode points to
        // a next Pokenode and the new Pokemon's pokemon_id is greater than
        //  the current Pokemon's pokemon_id.
        while (current->next != NULL && id > pokemon_id(current->pokemon)) {
            current = current->next;
        }

        // Connect the new Pokenode to its next and previous Pokenodes
        struct pokenode *next = current->next;
        current->next = new;
        new->prev = current;
        new->next = next;
        // If next is NULL, then the new Pokenode is being inserted at the
        // end of the Pokedex and next is not a struct.
        if (next != NULL) {
            next->prev = new;
        }

    }
}

// Returns whether a given string contains another string
static int str_contains(char *string, char *search_string) {
    int string_length = str_length(string);
    int search_string_length = str_length(search_string);

    // Return `0` if the string is shorter than `search_string` as
    // there are not enough characters in it.
    if (string_length < search_string_length) {
        return 0;
    }
    
    int i = 0;
    int substr_length = 0;
    // Iterate through `string` while there are more characters to check
    // and the string has not been found
    while (i < string_length && substr_length != search_string_length) {
        if (toLower(string[i]) == toLower(search_string[substr_length])) {
            // if the characters are equal, increment the length of the
            // matching substring
            substr_length++;
        } else if (toLower(string[i]) == toLower(search_string[0])) {
            // If the current character is equal to the first character of 
            // `search_string`, set `substr_length` to `1` to restart checking 
            // whether `search_string` is in `string`
            substr_length = 1;
        } else {
            // if the characters are different, reset the matching substring
            // length to `0`
            substr_length = 0;
        }
        i++;
    }

    // If the lengths are the same, then `string` contains `search_string`
    if (substr_length == search_string_length) {
        return 1;
    }

    return 0;  
    
}

// Returns the lowercase version of a given latin alphabet 
// character
static char toLower(char ch) {
    // If the character is an uppercase letter, convert it to lowercase
    if (ch >= 'A' && ch <= 'Z') {
        int position = ch - 'A';
        return 'a' + position;
    }
    // Otherwise return the input character
    return ch;
}

// Handle all errors for which the program should exit
static void handle_error(enum error_type error) {
    char *message = "An error occurred";
    
    if (error == NEW_POKEMON_SAME_ID) {
        message = "There's already a Pokemon with that `pokemon_id`!";
    } else if (error == EMPTY_POKEDEX) {
        message = "The Pokedex is empty! Add a Pokemon first.";
    } else if (error == NO_CURRENT_POKEMON) {
        message = "No current pokemon! Add a Pokemon first.";
    } else if (error == EVOLUTION_SAME_ID) {
        message = "Invalid evolution! `from_id` and `to_id` are the same.";
    } else if (error == EVOLUTION_NO_FROM_POKEMON) {
        message = "Invalid evolution! No Pokemon with that `from_id`";
    } else if (error == EVOLUTION_NO_TO_POKEMON) {
        message = "Invalid evolution! No Pokemon with that `to_id`";
    }

    // Print the error message and exit
    fprintf(stderr, "pokedex: %s\n", message);
    exit(1);
}