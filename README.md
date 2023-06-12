# listmv
A library that adds list/dictionary support to your C program.

TODO: everything.

# Example code
Lists:
```c
#include <stdio.h>
// turn the list GC off
#define LISTMV_GC false
#include <listmv.h>

int main() {
    listmv(char) name;
    listmv_init(name);

    listmv_push_array(name, "smv\n");

    // in theory this only works with char lists
    printf("Hello, %s\n", listmv_str_unwrap(name));

    listmv_delete(name); // if the GC is on this is taken care of
}

```

Dicts:
```c
#include <stdio.h>
// turn the list GC off
#define LISTMV_GC false
#include <listmv.h>

int main() {
    dictmv(int, float) dict;
    dictmv_push(dict, 420, 6.9);
    dictmv_push(dict, 122, 8.5);
    float CGPA = dictmv_get_key_for(dict, 420); // 6.9
    int ID = dictmv_get_value_for(dict, 3.5);   // 133

    dictmv_delete(dict); // if the GC is on this is taken care of
}
```

# Build and Install
TODO

### Notes
Work in progress.