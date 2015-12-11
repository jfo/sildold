#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "environments.c"

cell* quote(cell* operand) {
    if (operand->next == &nil) {
        return copycell(operand);
    } else {
        printf("'quote' accepts only one argument.\n\n");
        exit(1);
    }
}

cell* eval(cell *c, env *e) {
    if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *r = quote(c->value.list->next);
        r->next = eval(c->next, e);
        c = r;
        return c;
    } else if (c->type == LIST) {
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
/*     cell* operator = c->value.list; */
/*     cell* first_operand = c->value.list->next; */

/*     if (strcmp(operator->value.label, "quote") == 0) { */
/*         return quote(first_operand); */
/*     } else if (strcmp(operator->value.label, "atom") == 0) { */
/*         /1* return atom(first_operand); *1/ */
/*     } */
/* } */

int main() {
    env env = {"hello", "hi", NULL};

    cell* list = makelist("(hello ''hello)");
    debuglist(list);
    debuglist(eval(copycell(list), &env));
    printlist(list);
    printf("\n");
    printlist(eval(copycell(list), &env));
    return 0;
}
