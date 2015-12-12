int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ',' || c == ';'); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}


cell * read(char** s) {
    if (*s[0] == ' ' || *s[0] == '\n' || *s[0] == ',') {
        *s += 1;
        return read(s);
    /* } else if (*s[0] == '\'') { */
    /*     *s += 1; */
    /*     cell *in = read(s); */
    /*     cell *quote = makecell(LABEL, (value){.label = "quote"}, in); */
    /*     return makecell(LIST, (value){.list = quote}, read(s)); */
    } else if (*s[0] == '(') {
        *s += 1;
        return makecell(LIST, (value){.list=read(s)}, read(s));
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

        return makecell( LABEL, (value){.label=out}, read(s));
    }
}
