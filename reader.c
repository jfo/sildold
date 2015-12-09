int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ',' || c == ';'); };

int count_list_length(char* s) {
    int depth = 1;
    int count = 0;
    for (int i = 1; depth != 0; i++) {
        if (s[i] == '(') {
            depth++;
        } else if (s[i] == ')') {
            depth--;
        }
        count++;
    }
    return count + 1;
}

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}

char* return_substring(char* s){
    char* out = malloc(count_substring_length(s));
    int i = 0;
    while((isNotDisallowedChar(s[i]))) { out[i] = s[i]; i++; }
    out[i] = '\0';
    return out;
}

cell * makelist(char* s) {
    if (s[0] == ' ' || s[0] == '\n' || s[0] == ',') {
        return makelist(s + 1);
    } else if (s[0] == '\'' && s[1] == '(') {
        cell* quote = malloc(sizeof(cell));
        quote->type = LABEL;
        quote->value.label = "quote";

        cell* input = malloc(sizeof(cell));
        input->type = LIST;
        input->value.list = makelist(s+2);
        input->next = &nil;

        cell* output = malloc(sizeof(cell));
        output->type = LIST;
        output->value.list = quote;
        quote->next = input;
        output->next = makelist(s + count_list_length(s + 1) + 2);
        return output;
    } else if (s[0] == '\'') {
        cell* quote = malloc(sizeof(cell));
        quote->type = LABEL;
        quote->value.label = "quote";

        cell* input = malloc(sizeof(cell));
        input->type = LABEL;
        input->value.label = return_substring(s+1);
        input->next = &nil;

        cell* output = malloc(sizeof(cell));
        output->type = LIST;
        output->value.list = quote;
        quote->next = input;
        output->next = makelist(s + count_substring_length(s));
        return output;
    } else if (s[0] == ')') {
        return &nil;
    } else if (s[0] == '(') {
        union value input = { .list = makelist(s + 1) };
        return makecell( LIST, input, makelist(s + count_list_length(s)));
    } else if (s[0] == '\0') {
        /* you made it to the end of the input */
        return &nil;
    } else {
        union value input = { .label = return_substring(s) };
        return makecell( LABEL, input, makelist(s + count_substring_length(s)));
    }
}
