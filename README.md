# listmv
A library that adds list/dictionary support to your C program.

## Contents
- [Example code](#example-code)
- [Build and Install](#build-and-install)
- [Notes](#notes)
- [TODO](#todo)

## Example code
Lists:
```c
#include <stdio.h>
#include <listmv.h>

int main() {
    listmv name = new_listmv(char);

    listmv_push_array(&name, "smv\n", 5);

    printf("char at 2 %c\n", listmv_i(&name, 2)); // v
    // in theory this only works with char lists
    printf("Hello, %s\n", listmv_str_unwrap(name));

    listmv_free(name); // if the GC is on this is taken care of

    return 0;
}
```

Dicts (majorly TODO): This is how dictionaries could be used once I implement them:
```c
#include <stdio.h>
#include <listmv.h>

int main() {
    dictmv dict = new_dictmv(int, float);
    dictmv_push(dict, 420, 6.9);
    dictmv_push(dict, 122, 8.5);
    float CGPA = dictmv_get_key_for(dict, 420); // 6.9
    int ID = dictmv_get_value_for(dict, 3.5);   // 133

    dictmv_free(dict); // if the GC is on this is taken care of
}
```

**To use the GC** just use the `start_gc()` function. Note that there's no `stop_gc` for a reason.

## Build and Install
The GC and part of dictmv is still a work in progress. However you can still build using
```sh
make build
```
to generate headers and object at ./lib

Or install globally (Linux only) using
```sh
make install
```
to use it in any of your projects.


## Notes
Work in progress.

## TODO:
- dictmv functionality