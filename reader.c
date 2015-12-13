int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ','); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}

cell* read(char**);

cell * read_next(char** s, int depth) {
    if (*s[0] == ' ' || *s[0] == '\n' || *s[0] == ',') {
        *s += 1;
        return read_next(s, depth);
    } else if (*s[0] == '\'') {
        *s += 1;
        cell *quote = makecell(LABEL, (value){.label = "quote"}, read_next(s, 0));
        cell* next = ((depth > 0) ? read_next(s, depth) : &nil);
        return makecell(LIST, (value){.list = quote}, next);
    } else if (*s[0] == '(') {
        *s += 1;
        cell* listval = read_next(s, depth++);
        *s += 1;
        return makecell(LIST, (value){.list=listval}, &nil);
    } else if (*s[0] == ')' || *s[0] == '\0') {
        *s += 1;
        return &nil;
    } else {
        char* out = malloc(count_substring_length(*s));
        int i = 0;
        while((isNotDisallowedChar(**s))) {
            out[i] = **s;
            i++;
            *s += 1;
        }
        out[i] = '\0';
        cell* next = ((depth > 0) ? read_next(s, depth) : &nil);
        return makecell( LABEL, (value){.label=out}, next);
    }
}

cell * read(char** s) {
    if (*s[0] == ' ' || *s[0] == '\n' || *s[0] == ',') {
        ++*s;
        return read(s);
    } else if (*s[0] == '\'') {
        ++*s;
        cell *quote = makecell(LABEL, (value){.label = "quote"}, read_next(s, 0));
        return makecell(LIST, (value){.list = quote}, read(s));
    } else if (*s[0] == '(') {
        ++*s;
        return makecell(LIST, (value){.list=read_next(s, 1)}, read(s));
    } else if (*s[0] == ')' || *s[0] == '\0') {
        ++*s;
        return &nil;
    } else {
        cell* out = read_next(s,0);
        out->next = read(s);
        return out;
    }
}
