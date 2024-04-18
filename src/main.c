#include <stdio.h>

#include "my_api.h"

int main(int argc, char* argv[])
{

    my_struct_handle my_test_struct = create_a_my_struct();

    print_struct(my_test_struct);

    printf("Testing int\n\n");

    set_int(my_test_struct, -1);

    print_struct(my_test_struct);

    set_int(my_test_struct, 2);

    print_struct(my_test_struct);

    printf("\nTesting double\n\n");

    set_double(my_test_struct, 1.0);

    print_struct(my_test_struct);

    set_double(my_test_struct, 3.5);

    print_struct(my_test_struct);

    printf("\nTesting strings\n\n");

    set_string(my_test_struct, "Not starting with H", STATIC);

    print_struct(my_test_struct);

    set_string(my_test_struct, "Hello", STATIC);
    set_string(my_test_struct, "Hi", DYNAMIC);

    print_struct(my_test_struct);

    printf("\nTesting gets\n\n");

    printf("Our get product result: %f\n", get_product(my_test_struct));

    char *our_dynamic_string_copy = get_string(my_test_struct, DYNAMIC);

    printf("Dynamic string copy: %s\n", our_dynamic_string_copy);

    print_struct(my_test_struct);

    my_struct_handle second_struct = create_a_my_struct();

    set_double(second_struct, 5.0);

    printf("Multiplied stucts = %f\n", get_multiplied_structs(my_test_struct, second_struct));

    return 0;
}

