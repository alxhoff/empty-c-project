#include <stdio.h>

#include "my_api.h"

int main(int argc, char* argv[])
{
    print_struct();

    printf("Testing int\n\n");

    set_int(-1);

    print_struct();

    set_int(2);

    printf("\nTesting double\n\n");

    set_double(1.0);

    print_struct();

    set_double(3.5);

    printf("\nTesting strings\n\n");

    set_string("Not starting with H", STATIC);

    print_struct();

    set_string("Hello", STATIC);
    set_string("Hi", DYNAMIC);

    print_struct();

    printf("\nTesting gets\n\n");

    printf("Our get product result: %f\n", get_product());

    char *our_dynamic_string_copy = get_string(DYNAMIC);

    printf("Dynamic string copy: %s\n", our_dynamic_string_copy);


    print_struct();

    return 0;
}

