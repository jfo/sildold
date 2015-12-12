int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ',' || c == ';'); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}

char* return_substring(char** s) {
    char* out = malloc(count_substring_length(*s));
    int i = 0;
    while((isNotDisallowedChar(**s))) {
        out[i] = **s;
        i++;
        *s += 1;
    }
    out[i] = '\0';
    return out;
};

cell * makelist(char** s) {
    if (*s[0] == ' ' || *s[0] == '\n' || *s[0] == ',') {
        *s += 1;
        return makelist(s);
    } else if (*s[0] == '(') {
        *s += 1;
        return makecell( LIST, (value){.list=makelist(s)}, makelist(s));
    } else if (*s[0] == ')' || *s[0] == '\0') {
        *s += 1;
        return &nil;
    } else {
        return makecell( LABEL, (value){.label=return_substring(s)}, makelist(s));
    }
}
