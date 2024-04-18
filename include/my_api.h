#define STATIC 0
#define DYNAMIC 1

typedef void *my_struct_handle;

my_struct_handle create_a_my_struct(void);

void print_struct(my_struct_handle str);

double get_product(my_struct_handle str);
char *get_string(my_struct_handle str, char flag);
double get_multiplied_structs(my_struct_handle s1, my_struct_handle s2);

int set_int(my_struct_handle str, int my_int);
int set_double(my_struct_handle str, double my_double);
int set_string(my_struct_handle str, char *new_string, char flag);

