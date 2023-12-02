#include <stdio.h>
#include "../listmv.h"

int main() {
    listmv name = new_listmv(char);

    listmv_push_array(&name, "smv\n", 5);

    printf("char at 2 %c\n", listmv_i(&name, 2)); // v
    // in theory this only works with char lists
    printf("Hello, %s\n", listmv_str_unwrap(&name));

    listmv_free(&name); // if the GC is on this is taken care of

    return 0;
}
