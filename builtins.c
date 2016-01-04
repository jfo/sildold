cell*apply(cell*, cell**);
cell*eval(cell*, cell**);

cell* copy_cell(cell* n) {
    if (n->type == LIST) {
        return makecell(LIST, (value) { .list = copy_cell(n->value.list) }, copy_cell(n->next));
    } else if (n->type == LABEL) {
        return makecell(LABEL, (value){.label=n->value.label}, copy_cell(n->next));
    } else if (n->type == BUILTIN) {
        return makecell(BUILTIN, (value){.builtin=n->value.builtin}, copy_cell(n->next));
    } else if (n->type == INT) {
        return makecell(INT, (value){.num=n->value.num}, copy_cell(n->next));
    } else {
        return &nil;
    }
}

cell* copy_single_cell(cell* n) {
    if (n->type == LIST) {
        return makecell(LIST, (value) { .list = copy_cell(n->value.list) }, &nil);
    } else if (n->type == LABEL) {
        return makecell(LABEL, (value){.label=n->value.label}, &nil);
    } else if (n->type == BUILTIN) {
        return makecell(BUILTIN, (value){.builtin=n->value.builtin}, &nil);
    } else if (n->type == INT) {
        return makecell(INT, (value){.num=n->value.num}, &nil);
    }
    return &nil;
}

cell* quote(cell* operand) {
    if (operand->next == &nil) {
        return operand;
    } else {
        printf("\n\n'quote' accepts only one argument.\n\n");
        exit(1);
    }
}

cell* atom(cell* operand) {
    if (
            (operand->type == INT && operand->next == &nil)
            ||
            (operand->type == BUILTIN && operand->next == &nil)
            ||
            (operand->type == LABEL && operand->next == &nil)
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
            first->type == LABEL
            &&
            second->type == LABEL
            &&
            strcmp(first->value.label, second->value.label) == 0
            &&
            operand->next->next == &nil
            )
    {
        return &truth;
    } else if (
            first->type == INT
            &&
            second->type == INT
            &&
            first->value.num == second->value.num
            &&
            operand->next->next == &nil
            )
    {
        return &truth;
    } else if (operand->next->next != &nil) {
        printf("'eq' accepts only two arguments.\n\n");
        exit(1);
    } else {
        return &nil;
    }
}

cell* car(cell* operand) {
    cell * first = operand;
    if (first->type == LIST && operand->next == &nil) {
        return copy_single_cell(first->value.list);
    } else {
        return &nil;
    }
}

cell* cdr(cell* operand) {
    cell* first = operand;

    if (first->type == LIST && operand->next == &nil) {
        return makecell(LIST, (value){ .list = copy_cell(first->value.list->next) }, copy_cell(first->next));
    }
    return &nil;
}

cell* cons(cell* operands) {
    cell* first = operands;
    cell* second = operands->next;

    cell* output = malloc(sizeof(cell));
    output->type = LIST;
    output->value.list = copy_single_cell(first);
    output->value.list->next = copy_cell(second->value.list);
    output->next = &nil;
    return output;
}

cell* cond(cell* operands, cell *dict) {
    if (operands == &nil) {
        return &nil;
    }
    if (eval(copy_single_cell(operands->value.list), &dict) == &truth) {
        return copy_cell(eval(copy_single_cell(operands->value.list->next), &dict));
    } else {
        return cond(operands->next, dict);
    }
}

cell* assoc(char* key, cell *dict) {
    if (dict->value.list == &nil) {
        return &nil;
    } else if (strcmp(key, dict->value.list->value.list->value.label) == 0) {
        return copy_single_cell(dict->value.list->value.list->next);
    } else {
        return assoc(key, cdr(dict));
    }
};

cell* interleave(cell* a, cell* b, cell*dict) {
    if (a->value.list == &nil  || b->value.list == &nil) {
        return &nil;
    }
    cell* output = makecell(LIST, (value){.list = car(a) }, &nil);
    output->value.list->next = car(b);
    output->next = interleave(cdr(a), cdr(b), dict);
    return output;

};

cell* find_tail(cell* a) {
    if (a->next == &nil) {
        return a;
    } else {
        return find_tail(a->next);
    }
};

cell* lambda(cell *in, cell *dict){
    cell *new_dict = interleave(copy_single_cell(in->value.list->value.list->next), cdr(in), dict);
    cell* thing =  makecell(LIST, (value){.list = new_dict}, &nil);
    find_tail(thing->value.list)->next = copy_cell(dict->value.list);
    return eval(in->value.list->value.list->next->next, &thing);
};

cell* define(cell *in, cell **dict) {
    cell *new_dict = cdr(copy_cell(in));
    new_dict->value.list->next = eval(new_dict->value.list->next, dict);
    cell* thing =  makecell(LIST, (value){.list = new_dict}, &nil);
    thing->value.list->next = copy_cell((*dict)->value.list);
    *dict = thing;
    return &nil;
}

// MATHS
cell* add_inner(cell* operands, int acc) {
    if (operands == &nil) {
        return makecell(INT, (value){ .num = acc }, &nil);
    }
    return add_inner(operands->next, acc + operands->value.num);
}
cell* add(cell* input) {
    return add_inner(input, 0);
}

cell* subtract_inner(cell* operands, int acc) {
    if (operands == &nil) {
        return makecell(INT, (value){ .num = acc }, &nil);
    }
    return subtract_inner(operands->next, acc - operands->value.num);
}
cell* subtract(cell* input) {
    return subtract_inner(input->next, input->value.num);
}

cell* mult_inner(cell* operands, int acc) {
    if (operands == &nil) {
        return makecell(INT, (value){ .num = acc }, &nil);
    } else {
        return mult_inner(operands->next, acc * operands->value.num);
    }
}
cell* mult(cell* input) {
    return mult_inner(input, 1);
}

cell* divide_inner(cell* operands, int acc) {
    if (operands == &nil) {
        return makecell(INT, (value){ .num = acc }, &nil);
    } else {
        return divide_inner(operands->next, acc / operands->value.num);
    }
}
cell* divide(cell* input) {
    return divide_inner(input->next, input->value.num);
}

cell* modulo(cell* input) {
    return makecell(INT, (value){ .num = (input->value.num % input->next->value.num) }, &nil);
}
