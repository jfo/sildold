#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

cell* copy(cell* c) {
    if (c->type == LIST) {
        return makecell( LIST, (value){.list=copy(c->value.list)}, copy(c->next));
    } else if (c->type == LABEL) {
        return makecell( LABEL, (value){.label=c->value.label}, copy(c->next));
    } else {
        return &nil;
    }
        return &nil;
}

cell* eval(cell *c) {
    if (c->type == LIST) {
        eval(c->value.list);
        eval(c->next);
    } else if (c->type == LABEL) {
        return &nil;
    }
        return &nil;
}

/* cell* apply(cell *c){ */
/* } */

int main() {
    cell* list = makelist("(hello 'world)");
    debuglist(list);
    debuglist(copy(list));
    return 0;
}
