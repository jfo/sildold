#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

cell* define(cell *in, cell *dict) {
    cell *new_dict = cdr(in);
    cell* thing =  makecell(LIST, (value){.list = new_dict}, &nil);
    thing->value.list->next = copy_cell(dict->value.list);
    return thing;
}

cell* eval(cell *c, cell* dict) {
    if (c == &nil) {
        return &nil;
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *out = quote(c->value.list->next);
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "define") == 0) {
        return define(c, dict);
    } else if (
            c->type == LIST
            &&
            c->value.list->type == LIST
            &&
            strcmp(c->value.list->value.list->value.label, "lambda") == 0
            ) {
        return lambda(c, dict);
    } else if (c->type == LIST) {
        cell* out;
        out = apply(makecell(LIST,(value) { .list = eval(c->value.list, dict)}, &nil), dict);
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

cell* apply(cell *n, cell* dict) {
    cell* operator = n->value.list;
    cell* first_operand = n->value.list->next;

    if (strcmp(operator->value.label, "quote") == 0) {
        return quote(first_operand);
    } else if (strcmp(operator->value.label, "atom") == 0) {
        return atom(first_operand);
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
    } else if (operator->type == LIST && strcmp(operator->value.list->value.label, "lambda") == 0) {
        return lambda(n, dict);
    } else if (operator->type == LIST) {
        return eval(operator, dict);
    } else {
        printf("Attempted to apply non-procedure \"%s\"", operator->value.label);
        exit(1);
    }

    return &nil;
}

int main() {
    char* test = "((atom atom) (cons cons) (car car) (cdr cdr) (quote quote) (define define))";
    cell* testdict = read(&test);
    char* testl = "(define cadr (lambda (list) (car (cdr list))))";
    cell* testlist = read(&testl);

    char* testls = "(cadr '(1 2 3))";
    cell* testthing = read(&testls);
    debuglist(eval(testthing, eval(testlist, testdict)));
    return 0;
}
