#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "environments.c"

cell* evalapply(cell *);
cell* quote(cell* operand) {
    if (operand->next == &nil) {
        return copycell(operand);
    } else {
        printf("'quote' accepts only one argument.\n");
        exit(1);
    }
}

cell* atom(cell* operand) {
    if (
            (operand->type != LIST && operand->next == &nil)
            ||
            (operand->type == LIST && operand->value.list == &nil)
       ){
        return &truth;
    } else {
        return &nil;
    }
}

cell* eq(cell* operand) {
    cell* first = operand;
    cell* second = operand->next;

    if (
            (first->type == LIST && first->value.list == &nil)
            &&
            (second->type == LIST && second->value.list == &nil)
            &&
            operand->next->next == &nil
       )
    {
        return &truth;
    } else if (
            first->type != LIST
            &&
            second->type != LIST
            &&
            strcmp(first->value.label, second->value.label) == 0
            &&
            operand->next->next == &nil
            )
    {
        return &truth;
    } else if (operand->next->next != &nil) {
        printf("'eq' accepts only two arguments.\n");
        exit(1);
    } else {
        return &nil;
    }
}

cell* eval(cell *c) {
    if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *r = quote(c->value.list->next);
        r->next = eval(c->next);
        c = r;
        return c;
    } else if (c->type == LIST) {
        c->value.list = eval(c->value.list);
        c->next = eval(c->next);
        return c;
    } else if (c->type == LABEL) {
        /* if (read_entry(c->value.label)) { */
            /* c->value.label = read_entry(c->value.label); */
        /* } */
        c->next = eval(c->next);
        return c;
    }
    return c;
}

cell* apply(cell *c){
    cell* operator = c->value.list;
    cell* first_operand = c->value.list->next;

    if (strcmp(operator->value.label, "quote") == 0) {
        return quote(first_operand);
    } else if (strcmp(operator->value.label, "atom") == 0) {
        return atom(first_operand);
    } else if (strcmp(operator->value.label, "eq") == 0) {
        return eq(first_operand);
    } else {
        printf("Attempted to apply non-procedure: \"%s\"", operator->value.label);
        exit(1);
    }
}

cell* evalapply(cell *form) {
    return apply(eval(form));
}

int main() {

    cell* list = makelist("''hi");
    debuglist(list);
    /* debuglist(eval(list)); */
    /* debuglist(apply(list)); */
    return 0;
}
