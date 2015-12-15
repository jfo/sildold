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
        debuglistinner(l->next, depth++);
    }
}

void printlist(cell* l) {
    if (l->type == LIST) {
        printf("(");
        printlist(l->value.list);
        printlist(l->next);
    } else if (l->type == LABEL) {
        printf(" %s ", l->value.label);
        if (l->next == &nil) {
            printf(")");
        }
        printlist(l->next);
    }
}

void debuglist(cell* l) {
    printf("\n");
    debuglistinner(l, 0);
}
