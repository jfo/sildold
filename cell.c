
#include <stdio.h>
#include <stdlib.h>

enum { NIL, LABEL, LIST };

union value {
    char * label;
    struct cell * list;
};

struct cell {
    int type;
    union value value;
    struct cell * next;
};

typedef struct cell cell;

cell nil = { NIL, { "#f" }, 0x0 };
cell truth = { LABEL, {"#t"}, &nil };

cell* makecell(int type, union value val, cell * next) {
    if (type == NIL) {
        return &nil;
    } else {
        cell* output = malloc(sizeof(cell));
        output->type = type;
        output->value = val;
        output->next = next;
        return output;
    }
}
