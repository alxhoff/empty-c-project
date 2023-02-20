#ifndef __YAHTZEE_H__
#define __YAHTZEE_H__

/// @brief Cup structure that contains a collection of struct die objects
struct cup {
    struct die **dice;
    int dice_count;
};

/// @brief A die object that has a current and maximum value
struct die {
    int max_value;
    int current_value;
};

/// @brief Allocates the memory for a struct cup object and the pointer array
/// for the contained die objects.
/// @param dice_count Number of dice the cup should contain
/// @return Pointer to the struct cup object created
struct cup *create_cup(int dice_count);

/// @brief Fills our cup object with dice according to the number of dice it
/// can hold
///
/// When a cup is created using create_cup, the number of dice it holds it
/// specified with the argument `dice_count`, if we want to fill the cup we can
/// do so via this function that creates `dice_count` number of dice in the
/// cup object specified where the dice are configured to have a maximum value
/// specified by max_value.
///
/// @param cup_to_fill Pointer to the cup object that should be filled
/// @param max_value Maximum value that the dice should be able to have, eg.
/// standard dice would have a max_value of 6
/// @return 0 on success.
signed char fill_cup(struct cup *cup_to_fill, int max_value);

/// @brief Rolls all of the die in a cut via roll_die
/// @param current_cup Pointer to the cup object that should be rolled
void roll_cup(struct cup *current_cup);

/// @brief Prints the contents of a cup
/// @param current_cup Pointer to the cup object that should be rolled
void print_cup(struct cup *current_cup);

#endif
