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

my_struct_handle create_a_my_struct(void)
{

    struct my_struct_type *ret_struct =
        (struct my_struct_type *)calloc(1, sizeof(struct my_struct_type));

    if (ret_struct == NULL)
        return NULL;

    return (my_struct_handle)ret_struct;
}

struct my_stuct_type *_get_casted_pointer(my_struct_handle str)
{
    return (struct my_struct_type *)str;
}

void print_struct(my_struct_handle str)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

    printf("Summary:\nInt:%d\nDouble:%f\nStatic string:%s\nDynamic string:%s\n",
           casted_str->my_int, casted_str->my_double, casted_str->my_static_string,
           casted_str->my_dynamic_string);
}

double get_product(my_struct_handle str)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

    return casted_str->my_double * casted_str->my_int;
}

char *get_string(my_struct_handle str, char flag)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

    switch (flag)
    {
    case STATIC:
        return strdup(casted_str->my_static_string);
    case DYNAMIC:
        return strdup(casted_str->my_dynamic_string);
    }
}

double get_multiplied_structs(my_struct_handle s1, my_struct_handle s2)
{
    if (s1 == NULL || s2 == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str1 = _get_casted_pointer(s1);
    struct my_struct_type *casted_str2 = _get_casted_pointer(s2);
    
    return (double)casted_str1->my_int * casted_str2->my_double;
}

int set_int(my_struct_handle str, int my_int)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

    if (my_int < 0)
        return 1;

    casted_str->my_int = my_int;

    return 0;
}

int set_double(my_struct_handle str, double my_double)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

    if (my_double < 2.0)
        return 1;

    casted_str->my_double = my_double;

    return 0;
}

int set_string(my_struct_handle str, char *new_string, char flag)
{
    if (str == NULL)
    {
        printf("NULL handle passed to function\n");
        exit(1);
    }

    struct my_struct_type *casted_str = _get_casted_pointer(str);

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
        strcpy(casted_str->my_static_string, new_string);
        break;

    case DYNAMIC:
        if (casted_str->my_dynamic_string != NULL)
        { // we already have set a string
            if ((reallocarray(casted_str->my_dynamic_string, strlen(new_string) + 1, sizeof(char))) == NULL)
            {
                printf("Error reallocating string\n");
                return 4;
            }
        }
        else
        {
            casted_str->my_dynamic_string = calloc(strlen(new_string) + 1, sizeof(char));
            if (casted_str->my_dynamic_string == NULL)
            {
                printf("Failed to allocated string memory\n");
                return 5;
            }
        }
        // we know that the allocation was good if we get here
        strcpy(casted_str->my_dynamic_string, new_string);

        break;
    default:
        printf("Please provide a valid flat, either STATIC or DYNAMIC\n");
        return 2;
    }

    return 0;
}