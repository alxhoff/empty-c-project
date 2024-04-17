#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_api.h"

#define MAX_STRING_LENGTH MAX_STRING_CHARS + 1
#define MAX_STRING_CHARS 256

struct my_struct_type
{
    int my_int;
    double my_double;
    char my_static_string[MAX_STRING_LENGTH];
    char *my_dynamic_string;
};

struct my_struct_type my_struct = {0};

void print_struct(void)
{
    printf("Summary:\nInt:%d\nDouble:%f\nStatic string:%s\nDynamic string:%s\n",
           my_struct.my_int, my_struct.my_double, my_struct.my_static_string, my_struct.my_dynamic_string);
}

double get_product(void)
{
    return my_struct.my_double * my_struct.my_int;
}

char *get_string(char flag)
{
    switch (flag)
    {
    case STATIC:
        return strdup(my_struct.my_static_string);
    case DYNAMIC:
        return strdup(my_struct.my_dynamic_string);
    }
}

int set_int(int my_int)
{

    if (my_int < 0)
        return 1;

    my_struct.my_int = my_int;

    return 0;
}

int set_double(double my_double)
{

    if (my_double < 2.0)
        return 1;

    my_struct.my_double = my_double;

    return 0;
}

int set_string(char *new_string, char flag)
{

    if (new_string == NULL)
    {
        printf("The string provided to set_string is NULL\n");
        return 1;
    }

    if (new_string[0] != 'H')
    {
        printf("String must start with 'H'\n");
        return 6;
    }

    switch (flag)
    {
    case STATIC:
        if (strlen(new_string) > MAX_STRING_CHARS)
        {
            printf("String provided to set_string is too long\n");
            return 3;
        }
        strcpy(my_struct.my_static_string, new_string);
        break;

    case DYNAMIC:
        if (my_struct.my_dynamic_string != NULL) {// we already have set a string
            if ((reallocarray(my_struct.my_dynamic_string, strlen(new_string) + 1, sizeof(char))) == NULL)
            {
                printf("Error reallocating string\n");
                return 4;
            }
        }
        else
        {
            my_struct.my_dynamic_string = calloc(strlen(new_string) + 1, sizeof(char));
            if (my_struct.my_dynamic_string == NULL)
            {
                printf("Failed to allocated string memory\n");
                return 5;
            }
        }
        // we know that the allocation was good if we get here
        strcpy(my_struct.my_dynamic_string, new_string);

        break;
    default:
        printf("Please provide a valid flat, either STATIC or DYNAMIC\n");
        return 2;
    }

    return 0;
}