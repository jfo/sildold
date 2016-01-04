#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

cell* eval(cell *c, cell** dict) {
    if (c == &nil) {
        return &nil;
    } else if (c->type == BUILTIN || c->type == INT) {
        cell *out = c;
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LIST && c->value.list->value.builtin == LAMBDA) {
        return c;
    } else if (c->type == LIST && c->value.list->value.builtin == QUOTE) {
        cell *out = quote(c->value.list->next);
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LIST && c->value.list->value.builtin == DEFINE) {
        return define(c, dict);
    } else if (c->type == LIST && c->value.list->value.builtin == COND) {
        return cond(c->value.list->next, *dict);
    } else if (
            c->type == LIST
            &&
            c->value.list->type == LIST
            &&
            c->value.list->value.list->value.builtin ==  LAMBDA
            ) {
        return lambda(c, *dict);
    } else if (c->type == LIST) {
        cell* out;
        out = apply(makecell(LIST,(value) { .list = eval(c->value.list, dict)}, &nil), dict);
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LABEL) {
        cell *val = assoc(c->value.label, *dict);
        cell *out;
        if (val != &nil) {
             out = val;
        } else {
            debuglist(c);
            printf("Unbound variable: %s\n", c->value.label);
            exit(1);
        }
        out->next = eval(c->next, dict);
        return out;
    }
    return &nil;
}

cell* apply(cell *n, cell** dict) {
    cell* operator = n->value.list;
    cell* first_operand = n->value.list->next;

    if (operator->type == BUILTIN) {
        switch (operator->value.builtin) {
            case ATOM:
                return atom(first_operand);
            case EQ:
                return eq(first_operand);
            case CAR:
                return car(first_operand);
            case CDR:
                return cdr(first_operand);
            case CONS:
                return cons(first_operand);
            case ADD:
                return add(first_operand);
            case SUB:
                return subtract(first_operand);
            case MUL:
                return mult(first_operand);
            case DIV:
                return divide(first_operand);
            case MOD:
                return modulo(first_operand);
            case DISPLAY:
                printlist(n->value.list->next, 0);
            case QUOTE: {
                cell *out = quote(first_operand);
                out->next = eval(n->next, dict);
                return out;
            }
        }
    } else if (operator->type == LIST && operator->value.list->value.builtin ==  LAMBDA) {
        return lambda(n, *dict);
    } else if (operator->type == LIST) {
        return eval(operator, dict);
    } else {
        printf("Attempted to apply non-procedure \"%s\"", operator->value.label);
        exit(1);
    }

    return &nil;

}

int main(int argc, char *argv[]) {
    /* FILE *fp = NULL; */

    /* if ( argc != 2 ) { */
    /*     printf( "usage: %s filename", argv[0] ); */
    /* } else { */
    /*     fp = fopen( argv[1], "r" ); */
    /*     if ( fp == 0 ) { */
    /*         printf( "Could not open file\n" ); */
    /*     } */
    /* } */

    FILE *fp = fopen("examples/fizzbuzz.scm", "r");
    char c = getc(fp);
    /* this input mode is terrible. */
    char* ugh = malloc(sizeof(char) * 10000);
    int i = 0;

    while (c != EOF) {
        ugh[i] = c;
        i++;
        c = getc(fp);
    }

    ugh[i] = '\0';
    realloc(ugh, i);

    cell* standard_env = makecell(LIST, (value){.list = &nil}, &nil);

    while(*ugh != '\0') {
        cell* thing = read(&ugh, 0);
        eval(thing, &standard_env);
    }
    return 0;
}
