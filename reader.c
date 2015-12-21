int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ','); };
int isTerminalChar(char c) { return (c == '\0' || c == EOF); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}


const int builtins_len = 10;
const char * builtins[] = {
    "+",
    "eq",
    "quote",
    "lambda",
    "cond",
    "atom",
    "car",
    "cdr",
    "cons",
    "display",
};

int isbuiltin(char* input) {
    for (int i = 0; i < builtins_len; i++) {
        if (!strcmp(input, builtins[i])) {
            return 1;
        }
    };
    return 0;
}

int isint(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] < 48 || input[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int to_i(char* input) {
    int output = 0;
    for (int i = 0; i < strlen(input); i++) {
        int placer = 1;
        for (int j = i; j < strlen(input) - 1; j++) { placer *= 10; };
        output += ((int)input[i] - 48) * placer;
    }
    return output;
}

cell* categorize(char* c) {
    if (isbuiltin(c)) {
        return makecell(BUILTIN, (value){.label=c}, &nil);
    } else if (isint(c)) {
        return makecell(INT, (value){.num=to_i(c)}, &nil);
    } else {
        return makecell(LABEL, (value){.label=c}, &nil);
    }
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
