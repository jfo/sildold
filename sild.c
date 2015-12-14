#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

cell* eval(cell *c, cell* dict) {
    if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *r = quote(c->value.list->next);
        r->next = eval(c->next, dict);
        c = r;
        return c;
    } else if (c->type == LIST) {
        c->value.list = eval(c->value.list, dict);
        c->next = eval(c->next, dict);
        return c;
    } else if (c->type == LABEL) {
        cell *val = assoc(c->value.label, dict);
        if (val != &nil) {
            c = val;
        }
        c->next = eval(c->next, dict);
        return c;
    }
    return c;
}

int main() {

    /* char* test = "((that 7) (this 6))"; */
    char* test = "((tis 6) (this 8)(that x) (tat thing))";
    cell* list = read(&test);
    debuglist(eval(list, list));

    return 0;
}
