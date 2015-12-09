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

cell* makelist();

cell *quote_wrapper(cell* c, char* s) {
    union value quote_value = { .label = "quote" };
    cell *quote = makecell( LABEL, quote_value, c);
    union value output_value = { .list = quote };
    return makecell( LIST, output_value, makelist(s + count_list_length(s + 1) + 3));
}

cell * makelist(char* s) {
    if (s[0] == ' ' || s[0] == '\n' || s[0] == ',') {
        return makelist(s + 1);
    } else if (s[0] == '\'' && s[1] == '(') {
        union value list_value = { .list =  makelist(s+2) };
        cell *list = makecell( LIST, list_value, &nil);
        return quote_wrapper(list, s);
    } else if (s[0] == '\'') {
        union value label_value = { .label =  return_substring(s+1) };
        cell *label = makecell( LABEL, label_value, &nil);
        return quote_wrapper(label, s);
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
