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

cell *quote_wrapper(char* s, cell* c) {
    int offset = ((c->type == LIST) ? count_list_length(s + 1) + 1 : count_substring_length(s));
    cell *quote = makecell(LABEL, (value){.label="quote"}, c);
    return makecell(LIST, (value){.list = quote}, makelist(s + offset));
}

/* TODO: implement constant time reader function that needn't count string and list lengths
* probably by passing a pointer to a pointer and incrementing in place?
* Will allow me to get rid of the redundant iterations from counting functions above.
*/
cell * makelist(char* s) {
    if ((s[0] == ' ' || s[0] == '\n' || s[0] == ',') || (s[0] == '\'' && (s[1] == ' ' || s[1] == ','))) {
        return makelist(s + 1);
    } else if ((s[0] == '\'' && s[1] == '('))  {
        return quote_wrapper(s, makecell(LIST, (value){.list=makelist(s+2)}, &nil));
    } else if (s[0] == '\'' && s[1] == '\'')  {
        return quote_wrapper(s, makelist(s+1));
    } else if (s[0] == '\'') {
        return quote_wrapper(s, makecell(LABEL, (value){.label=return_substring(s+1)}, &nil));
    } else if (s[0] == ')' || s[0] == '\0') {
        return &nil;
    } else if (s[0] == '(') {
        return makecell( LIST, (value){.list=makelist(s+1)}, makelist(s + count_list_length(s)));
    } else {
        return makecell( LABEL, (value){.label=return_substring(s)}, makelist(s + count_substring_length(s)));
    }
}
