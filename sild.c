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
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "quote") == 0) {
        cell *out = quote(c->value.list->next);
        out->next = eval(c->next, dict);
        return out;
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "define") == 0) {
        return define(c, dict);
    } else if (c->type == LIST && strcmp(c->value.list->value.label, "cond") == 0) {
        return cond(c->value.list->next, *dict);
    } else if (
            c->type == LIST
            &&
            c->value.list->type == LIST
            &&
            strcmp(c->value.list->value.list->value.label, "lambda") == 0
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

    if (strcmp(operator->value.label, "atom") == 0) {
        return atom(first_operand);
    } else if (strcmp(operator->value.label, "eq") == 0) {
        return eq(first_operand);
    } else if (strcmp(operator->value.label, "car") == 0) {
        return car(first_operand);
    } else if (strcmp(operator->value.label, "cdr") == 0) {
        return cdr(first_operand);
    } else if (strcmp(operator->value.label, "cons") == 0) {
        return cons(first_operand);
    } else if (strcmp(operator->value.label, "+") == 0) {
        return add(first_operand);
    } else if (strcmp(operator->value.label, "display") == 0) {
        debuglist(n->value.list->next);
    } else if (strcmp(operator->value.label, "quote") == 0) {
        cell *out = quote(n->value.list->next);
        out->next = eval(n->next, dict);
        return out;
    } else if (operator->type == LIST && strcmp(operator->value.list->value.label, "lambda") == 0) {
        return lambda(n, *dict);
    } else if (operator->type == LIST) {
        return eval(operator, dict);
    } else {
        printf("Attempted to apply non-procedure \"%s\"", operator->value.label);
        exit(1);
    }

    return &nil;

}

int main() {
    FILE* fp = fopen("./test.scm", "r");
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
