int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ','); };
int isTerminalChar(char c) { return (c == '\0' || c == EOF); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}

cell* categorize(char* c) {
    return makecell( LABEL, (value){.label=c}, &nil);
}

cell * read(char** s, int depth) {
    if (**s == ';') {
        while(**s != '\n') {
            *s += 1;
        }
    };

    if (isTerminalChar(**s)) {
        exit(0);
    };

    if (*s[0] == ' ' || *s[0] == '\n' || *s[0] == ',') {
        *s += 1;
        return read(s, depth);
    } else if (*s[0] == '\'') {
        *s += 1;
        cell *quote = makecell(LABEL, (value){.label = "quote"}, read(s, 0));
        cell* next = ((depth > 0) ? read(s, depth) : &nil);
        return makecell(LIST, (value){.list = quote}, next);
    } else if (*s[0] == '(') {
        *s += 1;
        cell* listval = read(s, depth + 1);
        cell* next = ((depth > 0) ? read(s, depth) : &nil);
        return makecell(LIST, (value){.list=listval}, next);
    } else if (*s[0] == ')') {
        *s += 1;
        return &nil;
    } else {
        char* out = malloc(count_substring_length(*s));
        int i = 0;
        while(isNotDisallowedChar(**s)) {
            out[i] = **s;
            i++;
            *s += 1;
        }
        out[i] = '\0';
        cell* next = ((depth > 0) ? read(s, depth) : &nil);
        cell* outcell = categorize(out);
        outcell->next = next;
        return outcell;
    }
}
