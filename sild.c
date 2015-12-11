#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "environments.c"

cell* eval(cell *c, env *e) {
    if (c->type == LIST) {
        c->value.list = eval(c->value.list, e);
        c->next = eval(c->next, e);
        return c;
    } else if (c->type == LABEL) {
        if (read_entry(c->value.label, e)) {
            c->value.label = read_entry(c->value.label, e);
        }
        c->next = eval(c->next, e);
        return c;
    }
    return c;
}

/* cell* apply(cell *c){ */
/* } */

int main() {
    cell* list = makelist("(hello hello hello)");
    env env = {"hello", "hi", NULL};
    debuglist(eval(copycell(list), &env));
    return 0;
}
