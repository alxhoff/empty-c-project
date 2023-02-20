
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "yahtzee.h"

struct cup *create_cup(int dice_count)
{
    // Randomising number requires a seed which is used to generate random
    // numbers from, an easy to get and use seed is the time
    time_t t;
    // The srand function takes in an unsigned integer as its argument, thus
    // we can cast our time_t variable into an unsigned integer for use as a
    // seed
    srand((unsigned) time(&t));  //Cast time structure into random seed value

    // Allocates cup object
    struct cup *ret = (struct cup *)malloc(sizeof(struct cup));

    // Check memory allocation didn't fail
    if (!ret) {
        return NULL;
    }

    // Set the number of dice we want into our new cup structure
    ret->dice_count = dice_count;

    // Allocates list of empty pointers to die objects
    ret->dice = (struct die **)calloc(dice_count, sizeof(struct die *));

    printf("Cup created\n");

    // Return pointer to allocated cup object
    return ret;
}

signed char fill_cup(struct cup *cup_to_fill, int max_value)
{
    // Check that the cup object passed in is not a pointer to a null address
    if (cup_to_fill != NULL) {

        // Loop for the number of dice that need to be in the cup
        for (int i = 0; i < cup_to_fill->dice_count; i++) {

            // Create each die in the array
            cup_to_fill->dice[i] = (struct die *)malloc(sizeof(struct die));

            // Check that the memory allocation didn't fail
            if (!cup_to_fill->dice[i]) {
                return -1;    //Negative value on error
            }

            // Initialize our newly created die object to have a value of 0,
            // when rolled die can have a minimum value of 1, thus 0 represents
            // a die that has never been rolled
            cup_to_fill->dice[i]->current_value = 0;
            // Save the max value that the die can have locally in the die object
            cup_to_fill->dice[i]->max_value = max_value;

        }
        printf("Cup filled\n");
        return 0; //No errors
    }
    else {
        // Return a non-zero value to indicate an error
        return -1;
    }
}

/// @brief Rolles a die generating a value between 1 and it's configured maximum
/// value
/// @param cur_die Pointer to the die that should be rolled
void roll_die(struct die *cur_die)
{
    // Set current_value to random value between 1 and max_value
    cur_die->current_value = (rand() % cur_die->max_value) + 1;
}

void roll_cup(struct cup *current_cup)
{
    // Iterate through die and roll them
    for (int i = 0; i < current_cup->dice_count; i++) {
        roll_die(current_cup->dice[i]);
    }
}

void print_cup(struct cup *current_cup)
{
    // Iterate through the die in the cup and print their values in a formatted
    // string
    for (int i = 0; i < current_cup->dice_count; i++)
        // %d prints an integer value as part of a format string, printf takes
        // a format string as its argument
        printf("Die %d has a value of %d\n", i,
               current_cup->dice[i]->current_value);
}

