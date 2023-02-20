#include <stdio.h>
#include <stdlib.h>

#include "yahtzee.h"

#define ROLL 1
#define PRINT 2
#define EXIT 3

/// @brief A function that prompts the user for an integer value from the
/// terminal whilst displaying a provided message
/// @param message Pointer to string that should be shown to the user
/// @param value Pointer to the integer variable which should store the user's
/// input
void prompt_int(char *message, int *value)
{
retry:
    printf("%s: ", message);
    scanf("%d", value);

    if (!*value) {
        printf("You cannot enter zero\n");
        goto retry;
    }
}

/// @brief Prompts the user for a command input and then handles the selected
/// command, the user can roll the dics with r/R, print the dice with p/P or
/// exit with e/E.
/// @return 0 on error, else returns 1 when dice should be rolled, 2 when
/// dice should be printer and 3 when the program should be exited.
unsigned char prompt_user_command(void)
{
    char error_count = 0;
    char input;
retry:
    printf("Roll dice [r/R], print cup [p/P] or exit [e/E]:");
    input = getchar(); // Gets next char from stdin stream

    switch (input) {
        case 'r':
        case 'R':
            getchar();
            return ROLL;
        case 'p':
        case 'P':
            getchar();
            return PRINT;
        case 'e':
        case 'E':
            getchar();
            return EXIT;
        default:
            if (input != '\n')
                while ((input = getchar()) != '\n' && input != EOF)
                    ;

            error_count++;
            printf("Invalid input\n");
            if (error_count < 3) {
                goto retry;
            }
            else {
                return 0; // Zero on error
            }
    }
}

// Where our program starts from
int main(int argc, char *argv[])
{
    int max_value = 0, dice_count = 0;

    prompt_int("Please enter the max value of each die", &max_value);
    prompt_int("Please enter the number of die in the cup", &dice_count);

    // A pointer to hold the address of the cup object returned from create_cup
    struct cup *my_cup = NULL;
    my_cup = create_cup(dice_count);

    int ret;
    // Creates all the die objects we want in our cup
    ret = fill_cup(my_cup, max_value);
    if (ret) {
        // Filling failed
        exit(EXIT_FAILURE);
    }

    getchar(); // Clear stdin

roll_again:
    // Get a command from the user to decide what to do next
    ret = prompt_user_command();
    if (ret == ROLL) {
        // roll all the dice in the cup
        roll_cup(my_cup);
        for (int i = 0; i < my_cup->dice_count; i++) {
            printf("%d: %d\n", i, my_cup->dice[i]->current_value);
        }
        goto roll_again;
    }
    else if (ret == PRINT) {
        // print the value's of all the dice in our cup
        print_cup(my_cup);
        goto roll_again;
    }
    else if (ret == EXIT) {
        // quit the program
        exit(EXIT_SUCCESS);
    }
    else {
        printf("Too many invalid input attempts, exiting\n");
        exit(EXIT_FAILURE);
    }
}
