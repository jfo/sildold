#include <stdio.h>
#include <stdlib.h>

enum { NIL, LABEL, LIST, BUILTIN, INT };

typedef union value {
    char * label;
    int num;
    struct cell * list;
} value;

typedef struct cell {
    int type;
    union value value;
    struct cell * next;
} cell;

cell nil = { NIL, { 0x0 }, 0x0 };
cell truth = { LABEL, {"#t"}, &nil };

cell* makecell(int type, value val, cell * next) {
    cell* output = malloc(sizeof(cell));
    output->type = type;
    output->value = val;
    output->next = next;
    return output;
}

void freecell(cell* l) {
    if (l == &nil) {
        return;
    } else if (l->type == LIST) {
        free(l);
        freecell(l->value.list);
        freecell(l->next);
    } else if (l->type == LABEL) {
        free(l);
        freecell(l->next);
    }
}
