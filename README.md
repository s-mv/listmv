# listmv
A library that adds list/dictionary support to your C program.

TODO: most things, but mainly GC.

# Example code
Lists:
```c
#include <stdio.h>
#include <listmv.h>

int main() {
    listmv(char) name = listmv_init();

    listmv_push_array(name, "smv\n");

    printf("char at 2 %c\n", listmv_i(name, 2)); // v
    // in theory this only works with char lists
    printf("Hello, %s\n", listmv_str_unwrap(name));

    listmv_delete(name); // if the GC is on this is taken care of

    return 0;
}
```

Dicts:
```c
#include <stdio.h>
#include <listmv.h>

int main() {
    dictmv(int, float) dict = dictmv_init();
    dictmv_push(dict, 420, 6.9);
    dictmv_push(dict, 122, 8.5);
    float CGPA = dictmv_get_key_for(dict, 420); // 6.9
    int ID = dictmv_get_value_for(dict, 3.5);   // 133

    dictmv_delete(dict); // if the GC is on this is taken care of
}
```

**To use the GC** just use the `start_gc()` function. Note that there's no `stop_gc` for a reason.

# Build and Install
TODO

### Notes
Work in progress.