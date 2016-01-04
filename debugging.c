void printtabs(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

void debuglistinner(cell* l, int depth) {
    if (l == &nil) {
        printtabs(depth);
        printf("NIL: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next);
        printtabs(depth - 1);
        printf("-----------------------------\n");
    } else if (l->type == LIST) {
        printtabs(depth);
        printf("-----------------------------\n");
        printtabs(depth);
        printf("LIST: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next);
        debuglistinner(l->value.list, depth + 1);
        debuglistinner(l->next, depth);
    } else if (l->type == LABEL) {
        printtabs(depth);
        printf("LABEL: addr:%p, value=%s, next_item=%p  \n", l, l->value.label, l->next);
        debuglistinner(l->next, depth);
    } else if (l->type == BUILTIN) {
        printtabs(depth);
        printf("BUILTIN: addr:%p, value=%s, next_item=%p  \n", l, builtins[l->value.builtin], l->next);
        debuglistinner(l->next, depth);
    } else if (l->type == INT) {
        printtabs(depth);
        printf("INT: addr:%p, value=%i, next_item=%p  \n", l, l->value.num, l->next);
        debuglistinner(l->next, depth++);
    }
}

void printlist(cell* l, int depth) {
    if (l == &nil && depth > 0) {
        printf(") ");
    } else if (l->type == LIST) {
        printf("( ");
        printlist(l->value.list, depth + 1);
        printlist(l->next, depth);
    } else if (l->type == BUILTIN) {
        printf("%s ", builtins[l->value.builtin]);
        printlist(l->next, depth);
    } else if (l->type == LABEL) {
        printf("%s ", l->value.label);
        printlist(l->next, depth);
    } else if (l->type == INT) {
        printf("%i ", l->value.num);
        printlist(l->next, depth);
    }
}

void debuglist(cell* l) {
    printf("\n");
    debuglistinner(l, 0);
}
