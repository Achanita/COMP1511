// Assignment 2 19T3 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by Soorriamoorthy S Saruva (z5258068)
// on 24-11-19
//
// Version 1.4.1: Add test_get_next_evolution

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// Sample data on Bulbasaur, the Pokemon with pokemon_id 1.
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Sample data on Ivysaur, the Pokemon with pokemon_id 2.
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE

// Add your own #defines here.

// Sample data on Venusaur, the Pokemon with pokemon_id 2.
#define VENUSAUR_ID 3
#define VENUSAUR_NAME "Venusaur"
#define VENUSAUR_HEIGHT 2.0
#define VENUSAUR_WEIGHT 100.0
#define VENUSAUR_FIRST_TYPE GRASS_TYPE
#define VENUSAUR_SECOND_TYPE POISON_TYPE

// Sample data on Arceus, the Pokemon with pokemon_id 493.
#define ARCEUS_ID 493
#define ARCEUS_NAME "Arceus"
#define ARCEUS_HEIGHT 3.2
#define ARCEUS_WEIGHT 320.0
#define ARCEUS_FIRST_TYPE NORMAL_TYPE
#define ARCEUS_SECOND_TYPE NONE_TYPE

// Sample data on Stakataka, the Pokemon with pokemon_id 805.
#define STAKATAKA_ID 805
#define STAKATAKA_NAME "Stakataka"
#define STAKATAKA_HEIGHT 5.5
#define STAKATAKA_WEIGHT 820.0
#define STAKATAKA_FIRST_TYPE ROCK_TYPE
#define STAKATAKA_SECOND_TYPE STEEL_TYPE

// Sample data on Onix, the Pokemon with pokemon_id 95.
#define ONIX_ID 95
#define ONIX_NAME "Onix"
#define ONIX_HEIGHT 8.8
#define ONIX_WEIGHT 210.0
#define ONIX_FIRST_TYPE ROCK_TYPE
#define ONIX_SECOND_TYPE GROUND_TYPE

// Add your own prototypes here.

static void test_prev_pokemon(void);
static void test_get_current_pokemon(void);
static void test_go_exploring(void);
static void test_remove_pokemon(void);
static void test_get_next_evolution(void);
static void test_get_pokemon_of_type(void);
static void test_search_pokemon(void);

static Pokemon create_venusaur(void);
static Pokemon create_arceus(void);
static Pokemon create_stakataka(void);
static Pokemon create_onix(void);
static void print_test(int number);
static void print_info(char *message);
static void print_check(char *message);
static int str_length(char *string);
static int str_equal(char *string1, char *string2);

// Tests for Pokedex functions from pokedex.c.
static void test_new_pokedex(void);
static void test_add_pokemon(void);
static void test_get_found_pokemon(void);
static void test_next_pokemon(void);

// Helper functions for creating/comparing Pokemon.
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);

int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    // test_new_pokedex();
    // test_add_pokemon();
    // test_next_pokemon();
    // test_get_found_pokemon();
    // test_prev_pokemon();
    // test_get_current_pokemon();
    // test_go_exploring();
    // test_remove_pokemon();
    test_get_next_evolution();
    // test_get_pokemon_of_type();
    // test_search_pokemon();

    printf("\nAll Pokedex tests passed, you are Awesome!\n");
}

////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
//
// Note that it isn't possible to check whether destroy_pokedex has
// successfully destroyed/freed the Pokedex, so the best we can do is to
// call the function and make sure that it doesn't crash..
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_check("Checking that the returned Pokedex is not NULL");
    assert(pokedex != NULL);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur (using the helper
// functions in this file and the provided code in pokemon.c), and
// calling add_pokemon to add it to the Pokedex.
//
// It then creates the Pokemon Ivysuar and calls add_pokemon to add 
// it to the Pokedex.
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");

    Pokedex pokedex;
    Pokemon bulbasaur;
    Pokemon ivysaur;

    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    // TEST 1
    print_test(1);

    print_info("Creating Bulbasaur");
    bulbasaur = create_bulbasaur();

    print_info("Adding Bulbasaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    
    // TEST 2
    print_test(2);

    print_info("Creating Ivysaur");
    ivysaur = create_ivysaur();

    print_info("Adding Ivysaur to the Pokedex");
    add_pokemon(pokedex, ivysaur);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_next_pokemon` checks whether the next_pokemon function works
// correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, then checks that calling the
// next_pokemon function changes the currently selected Pokemon from
// Bulbasaur to Ivysaur.
//
// Then it tries moving to the next Pokemon when there is no next Pokemon,
// and checks that the currently selected Pokemon is still Ivysaur.
// 
// Finally, it creates a new Pokedex and then tries mowing to the next
// Pokemon when there are no Pokemon in the Pokedex.
static void test_next_pokemon(void) {
    printf("\n>> Testing next_pokemon\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    // TEST 1
    print_test(1);
    print_info("Adding Bulbasaur and Ivysaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    print_check("Checking that the current Pokemon is Bulbasaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    print_info("Moving to the next pokemon");
    next_pokemon(pokedex);

    print_check("Checking that the current Pokemon is Ivysaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    // TEST 2
    print_test(2);
    print_info("Moving to the next pokemon (there is no next pokemon)");
    next_pokemon(pokedex);

    print_check("Checking that the current Pokemon is still Ivysaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    // TEST 3
    print_test(3);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Moving to the next pokemon (there are no pokemon)");
    next_pokemon(pokedex);
    print_check("Checking that there is no error");

    
    destroy_pokedex(pokedex);

    printf(">> Passed next_pokemon tests!\n");
}

// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, sets Bulbasaur to be found, and
// then calls the get_found_pokemon function to get all of the Pokemon
// which have been found (which should be just the one, Bulbasaur).
//
// It then checks that Bulbasaur is the first pokemon in the new Pokedex
// even though Ivysaur is added first to the original Pokedex.
// 
// Then it checks that get_found_pokemon does not crash when the original
// Pokedex is empty.
//
// Finally, it checks that get_found_pokemon does not crash when there are 
// Pokemon in the original Pokedex, but they are not set to be found.
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    // TEST 1
    print_test(1);
    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    print_info("Adding Bulbasaur and Ivysaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    print_check("Checking that the current Pokemon is Bulbasaur");
    assert(get_current_pokemon(pokedex) == bulbasaur);

    print_info("Setting Bulbasaur to be found");
    find_current_pokemon(pokedex);

    print_info("Getting all found Pokemon");
    Pokedex found_pokedex = get_found_pokemon(pokedex);

    print_check("Checking the correct Pokemon were copied and returned");
    assert(count_total_pokemon(found_pokedex) == 1);
    assert(count_found_pokemon(found_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    print_info("Destroying both Pokedexes");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    // TEST 2
    print_test(2);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    bulbasaur = create_bulbasaur();
    Pokemon venusaur = create_venusaur();

    print_info("Adding Venusaur then Bulbasaur to the Pokedex");
    add_pokemon(pokedex, venusaur);
    add_pokemon(pokedex, bulbasaur);

    print_check("Checking that the current Pokemon is Venusaur");
    assert(get_current_pokemon(pokedex) == venusaur);

    print_info("Setting Venusaur and Bulbasaur to be found");
    find_current_pokemon(pokedex);
    next_pokemon(pokedex);
    find_current_pokemon(pokedex);
    prev_pokemon(pokedex);

    print_info("Getting all found Pokemon");
    found_pokedex = get_found_pokemon(pokedex);

    print_check("Checking that the current Pokemon in found_pokedex is Bulbasaur");
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    print_check("Checking the correct Pokemon were copied and returned");
    assert(count_total_pokemon(found_pokedex) == 2);
    assert(count_found_pokemon(found_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));
    next_pokemon(found_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), venusaur));


    print_info("Destroying both Pokedexes");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    // TEST 3
    print_test(3);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Getting all found Pokemon");
    found_pokedex = get_found_pokemon(pokedex);

    print_check("Checking that found_pokedex is empty");
    assert(count_total_pokemon(found_pokedex) == 0);
    assert(count_found_pokemon(found_pokedex) == 0);

    print_info("Destroying both Pokedexes");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    // TEST 4
    print_test(4);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Creating Bulbasaur");
    bulbasaur = create_bulbasaur();

    print_info("Adding Bulbasaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);

    print_info("Getting all found Pokemon");
    found_pokedex = get_found_pokemon(pokedex);

    print_check("Checking that found_pokedex is empty");
    assert(count_total_pokemon(found_pokedex) == 0);
    assert(count_found_pokemon(found_pokedex) == 0);

    print_info("Destroying both Pokedexes");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}

// Write your own Pokedex tests here!

// `test_prev_pokemon` checks whether the prev_pokemon function works correctly.
// 
// It does this by create two Pokemon: Bulbasaur and Ivysaur and adding them to
// the Pokedex. It then moves to the next pokemon and then calls prev_pokemon 
// and checks whether the current pokemon is Bulbasaur.
// 
// It then checks that the current Pokemon is still Bulbasaur when prev_pokemon
// is called and there is no previous Pokemon.
// 
// Finally, it creates a new Pokedex but does not add any Pokemon to it. It calls
// prev_pokemon and makes sure it does not crash when there are no Pokemon in the
// Pokedex.
static void test_prev_pokemon(void) {
    printf("\n>> Testing prev_pokemon\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    // TEST 1
    print_test(1);
    print_info("Adding Bulbasaur and Ivysaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    print_check("Checking that the current Pokemon is Bulbasaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    print_info("Moving to the next pokemon");
    next_pokemon(pokedex);

    print_info("Moving to the previous pokemon");
    prev_pokemon(pokedex);

    print_check("Checking that the current Pokemon is Bulbasaur again");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    // TEST 2
    print_test(2);
    print_info(
        "Moving to the previous pokemon (there is no previous pokemon)"
    );
    prev_pokemon(pokedex);

    print_check("Checking that the current Pokemon is still Bulbasaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    // TEST 3
    print_test(3);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Moving to the previous pokemon (there are no pokemon)");
    next_pokemon(pokedex);
    print_check("Checking that there is no error");

    
    destroy_pokedex(pokedex);

    printf(">> Passed prev_pokemon tests!\n");
}

// `test_get_current_pokemon` checks whether the get_current_pokemon function 
// works correctly.
// 
// It does this by creating the Pokemon Bulbasaur and adding it to the Pokedex.
// It then checks that the currently selected pokemon is Bulbasaur.
// 
// It then creates and adds the Pokemon Ivysaur to the Pokedex. Then it deletes
// the current Pokemon (Bulbasaur) from the Pokedex. It calls get_current_pokemon
// and checks that the current Pokemon is now Ivysaur.
static void test_get_current_pokemon(void) {
    printf("\n>> Testing get_current_pokemon\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    Pokemon bulbasaur = create_bulbasaur();

    // TEST 1
    print_test(1);
    print_info("Adding Bulbasaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);

    print_check("Checking that the current Pokemon is Bulbasaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    // TEST 2
    print_test(2);
    print_info(
        "Creating Ivysaur"
    );
    Pokemon ivysaur = create_ivysaur();

    print_info("Adding Ivysaur to the Pokedex");
    add_pokemon(pokedex, ivysaur);

    print_info("Removing the current Pokemon (Bulbasaur) from the Pokedex");
    remove_pokemon(pokedex);

    print_check("Checking that the current Pokemon is Ivysaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed get_current_pokemon tests!\n");
}

// `test_go_exploring` checks whether the go_exploring function works correctly.
//
// It does this by creating the Pokemon Bulbasaur and Arceus and adding them to
// the Pokedex. It calls go_exploring and then checks that both found were found
// with count_found_pokemon.
//
// Then it creates Bulbasaur and Ivysaur and adds them to a new Pokedex. It calls
// go_exploring and checks that only Bulbasaur was found.
//
// Finally it creates Bulbasaur, Ivysaur, Arceus, Stakataka, and Onix. It calls 
// go_exploring and checks that all but Ivysaur were found.
static void test_go_exploring(void) {
    printf("\n>> Testing go_exploring\n");

    // TEST 1
    print_test(1);

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Arceus");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon arceus = create_arceus();

    print_info("Adding Bulbasaur and Arceus to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, arceus);

    print_info("Going exploring");
    go_exploring(pokedex);

    print_check("Checking that both Pokemon were found");
    assert(count_found_pokemon(pokedex) == 2);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    // TEST 2
    print_test(2);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Creating Bulbasaur and Ivysaur");
    bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    print_info("Adding Bulbasaur and Ivysaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    print_info("Going exploring");
    go_exploring(pokedex);

    print_check("Checking that only Bulbasaur was found.");
    assert(count_found_pokemon(pokedex) == 1);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    // TEST 3
    print_test(3);
    print_info("Creating a new Pokedex");
    pokedex = new_pokedex();

    print_info("Creating Bulbasaur, Ivysaur, Arceus, Stakataka and Onix");
    bulbasaur = create_bulbasaur();
    ivysaur = create_ivysaur();
    arceus = create_arceus();
    Pokemon stakataka = create_stakataka();
    Pokemon onix = create_onix();

    print_info(
        "Adding Bulbasaur, Ivysaur, Arceus, Stakataka and Onix to the Pokedex"
    );
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, arceus);
    add_pokemon(pokedex, stakataka);
    add_pokemon(pokedex, onix);

    print_info("Going exploring");
    go_exploring(pokedex);

    print_check("Checking that Bulbasaur, Arceus, Stakataka and Onix were found.");
    printf("%d\n", count_found_pokemon(pokedex));
    assert(count_found_pokemon(pokedex) == 4);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed go_exploring tests!\n");
}

// `test_remove_pokemon` checks whether the remove_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur, Ivysaur and Venusaur and
// adding them to the Pokedex. It sets the currently selected Pokemon to 
// Ivysaur and deletes it. Afterwards, it checks that the Pokedex has correctly 
// changed the currently selected Pokemon to Venusaur.
// 
// Then it removes Venusaur and checks that the currently selected Pokemon had
// been changed to Bulbasaur.
//
// Finally it removes Bulbasaur and checks that the Pokedex is empty.
static void test_remove_pokemon(void) {
    printf("\n>> Testing remove_pokemon\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur, Ivysaur and Venusaur");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon venusaur = create_venusaur();

    print_info("Adding Bulbasaur, Ivysaur and Venusaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, venusaur);

    // TEST 1
    print_test(1);

    print_info("Changing current Pokemon to Ivysaur");
    change_current_pokemon(pokedex, IVYSAUR_ID);

    print_info("Removing current Pokemon (Ivysaur)");
    remove_pokemon(pokedex);

    print_check("Checking that a Pokemon was removed");
    assert(count_total_pokemon(pokedex) == 2);

    print_check("Checking that the current Pokemon is now Venusaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), venusaur));

    // TEST 2
    print_test(2);

    print_info("Removing current Pokemon (Venusaur)");
    remove_pokemon(pokedex);

    print_check("Checking that a Pokemon was removed");
    assert(count_total_pokemon(pokedex) == 1);

    print_check("Checking that the current Pokemon is now Bulbasaur");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    // TEST 3
    print_test(3);
    
    print_info("Removing current Pokemon (Bulbasaur)");
    remove_pokemon(pokedex);

    print_check("Checking that the Pokedex is now empty");
    assert(count_total_pokemon(pokedex) == 0);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed remove_pokemon tests!\n");
}

// `test_get_next_evolution` checks whether the get_next_evolution function
// works correctly.
//
// It does this by creating the Pokemon Bulbasaur, Ivysaur and Venusaur and
// adding them to the Pokedex. Then it sets Bulbasaur's evolutin to Ivysaur.
// Then it calls get_next_evolution and checks whether it returns Ivysaur's
// pokemon_id. 
//
// Then it sets Ivysaur's evolution to Venusaur and repeats the above method,
// this time checking whether get_next_evolution returns Venusaur's 
// pokemon_id.
//
// Finally, it sets the current Pokemon to Venusaur. Then it checks that 
// get_next_evolution returns DOES_NOT_EVOLVE as Venusaur has not been 
// set an evolution.
static void test_get_next_evolution(void) {
    printf("\n>> Testing go_exploring\n");

    print_info("Creating a new Pokedex");
    Pokedex pokedex = new_pokedex();

    print_info("Creating Bulbasaur, Ivysaur and Venusaur");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon venusaur = create_venusaur();

    print_info("Adding Bulbasaur, Ivysaur and Venusaur to the Pokedex");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, venusaur);

    // TEST 1
    print_test(1);

    print_info("Set Bulbasaur's evolution to Ivysaur");
    add_pokemon_evolution(pokedex, BULBASAUR_ID, IVYSAUR_ID);

    print_check("Checking that Bulbasaur's evolution is Ivysaur");
    assert(get_next_evolution(pokedex) == IVYSAUR_ID);

    // TEST 2
    print_test(2);

    print_info("Set current Pokemon to Ivysaur");
    change_current_pokemon(pokedex, IVYSAUR_ID);

    print_info("Set Ivysaur's evolution to Venusaur");
    add_pokemon_evolution(pokedex, IVYSAUR_ID, VENUSAUR_ID);

    print_check("Checking that Ivysaur's evolution is Venusaur");
    assert(get_next_evolution(pokedex) == VENUSAUR_ID);

    // TEST 3
    print_test(3);
    
    print_info("Set current Pokemon to Venusaur");
    change_current_pokemon(pokedex, VENUSAUR_ID);

    print_check("Checking that Venusaur that does not evolve");
    assert(get_next_evolution(pokedex) == DOES_NOT_EVOLVE);

    print_info("Destroying the Pokedex");
    destroy_pokedex(pokedex);

    printf(">> Passed go_exploring tests!\n");
}

////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
        BULBASAUR_ID, BULBASAUR_NAME,
        BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
        BULBASAUR_FIRST_TYPE,
        BULBASAUR_SECOND_TYPE);
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
        IVYSAUR_ID, IVYSAUR_NAME,
        IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
        IVYSAUR_FIRST_TYPE,
        IVYSAUR_SECOND_TYPE);
    return pokemon;
}

// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
//
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
//
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second)) && 
            (first != second) && 
            (pokemon_height(first) == pokemon_height(second)) && 
            (pokemon_weight(first) == pokemon_weight(second)) && 
            (pokemon_first_type(first) == pokemon_first_type(second)) && 
            (pokemon_second_type(first) == pokemon_second_type(second) &&
            str_equal(pokemon_name(first), pokemon_name(second)));
}

// Write your own helper functions here!

static void print_test(int number) {
    printf("    Test [%d]\n", number);
}

static void print_info(char *message) {
    printf("    ... %s\n", message);
}

static void print_check(char *message) {
    printf("       --> %s\n", message);
}


// Returns the length of a given string.
static int str_length(char *string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

// Returns whether the contents of two strings are equal.
static int str_equal(char *string1, char *string2) {
    int str1_length = str_length(string1);
    if (str1_length != str_length(string2)) {
        return 0;
    }
    int i = 0;
    while (i < str1_length) {
        if (string1[i] != string2[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Helper functions that create Pokemon
// Helper function to create Venusaur for testing purposes.
static Pokemon create_venusaur(void) {
    Pokemon pokemon = new_pokemon(
        VENUSAUR_ID, VENUSAUR_NAME,
        VENUSAUR_HEIGHT, VENUSAUR_WEIGHT,
        VENUSAUR_FIRST_TYPE,
        VENUSAUR_SECOND_TYPE);
    return pokemon;
}

// Helper function to create Arceus for testing purposes.
static Pokemon create_arceus(void) {
    Pokemon pokemon = new_pokemon(
        ARCEUS_ID, ARCEUS_NAME,
        ARCEUS_HEIGHT, ARCEUS_WEIGHT,
        ARCEUS_FIRST_TYPE,
        ARCEUS_SECOND_TYPE);
    return pokemon;
}

// Helper function to create Stakataka for testing purposes.
static Pokemon create_stakataka(void) {
    Pokemon pokemon = new_pokemon(
        STAKATAKA_ID, STAKATAKA_NAME,
        STAKATAKA_HEIGHT, STAKATAKA_WEIGHT,
        STAKATAKA_FIRST_TYPE,
        STAKATAKA_SECOND_TYPE);
    return pokemon;
}

// Helper function to create Onix for testing purposes.
static Pokemon create_onix(void) {
    Pokemon pokemon = new_pokemon(
        ONIX_ID, ONIX_NAME,
        ONIX_HEIGHT, ONIX_WEIGHT,
        ONIX_FIRST_TYPE,
        ONIX_SECOND_TYPE);
    return pokemon;
}