#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

cell*apply(cell*);

cell* eval(cell *c, cell* dict) {
    if (c == &nil) {
        return &nil;
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *out = quote(c->value.list->next);
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LIST) {
        cell* out;
        out = apply(makecell(LIST,(value) { .list = eval(c->value.list, dict)}, &nil));
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LABEL) {
        cell *val = assoc(c->value.label, dict);
        cell *out;
        if (val != &nil) {
             out = val;
        } else {
            printf("Unbound variable: %s\n", c->value.label);
            exit(1);
        }
        out->next = eval(c->next, dict);
        return out;
    }
    return &nil;
}

cell* apply(cell *n) {
    cell* operator = n->value.list;
    cell* first_operand = n->value.list->next;

    if (strcmp(operator->value.label, "quote") == 0) {
        return quote(first_operand);
    /* } else if (strcmp(operator->value.label, "label") == 0) { */
    /*     return label(first_operand); */
    } else if (strcmp(operator->value.label, "eq") == 0) {
        return eq(first_operand);
    } else if (strcmp(operator->value.label, "car") == 0) {
        return car(first_operand);
    } else if (strcmp(operator->value.label, "cdr") == 0) {
        return cdr(first_operand);
    } else if (strcmp(operator->value.label, "cons") == 0) {
        return cons(first_operand);
    /* } else if (strcmp(operator->value.label, "cond") == 0) { */
    /*     return cond(first_operand); */
    /* } else if (strcmp(operator->value.label, "label") == 0) { */
    /*     add_label(first_operand->value.label, copy_cell(first_operand->next)); */
    /*     return find_label(first_operand->value.label); */
    /* } else if (strcmp(operator->value.label, "lambda") == 0) { */
    /*     return quote(n); */
    /* } else if (operator->type == LIST && strcmp(operator->value.list->value.label, "lambda") == 0) { */
    /*     return eval(lambda(n)); */
    } else if (operator->type == LIST) {
    } else {
        printf("Attempted to apply non-procedure \"%s\"", operator->value.label);
        exit(1);
    }

    return &nil;
}

int main() {

    /* char* test = "((that 7) (this 6))"; */
    char* test = "((cons cons) (car car) (cdr cdr))";
    cell* testdict = read(&test);

    /* char* testl = "(cons 'this '(taht))"; */
    char* testl = "(cons 'derp (cons '(hi) '(hi)))";
    cell* testlist = read(&testl);
    debuglist(eval(testlist, testdict));

    return 0;
}
