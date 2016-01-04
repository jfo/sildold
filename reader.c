int isNotDisallowedChar(char c) { return !(c == '\0' || c == ')' || c == '(' || c == ' ' || c == '\n' || c == ','); };
int isTerminalChar(char c) { return (c == '\0' || c == EOF); };

int count_substring_length(char* s) {
    int i = 0;
    while(isNotDisallowedChar(s[i])) { i++; };
    return i;
}


const int builtins_len = 16;
enum builtin_vals {
    MUL,
    ADD,
    SUB,
    DIV,
    MOD,
    EQ,
    QUOTE,
    LAMBDA,
    COND,
    ATOM,
    CAR,
    CDR,
    CONS,
    DISPLAY,
    DEBUG,
    DEFINE
};
typedef enum builtin_vals builtin_vals;
const char * builtins[] = {
    "*",
    "+",
    "-",
    "/",
    "%",
    "eq",
    "quote",
    "lambda",
    "cond",
    "atom",
    "car",
    "cdr",
    "cons",
    "display",
    "debug",
    "define",
};

int isbuiltin(char* input) {
    for (int i = 0; i < builtins_len; i++) {
        if (!strcmp(input, builtins[i])) {
            return i + 1;
        }
    };
    return 0;
}

int isint(char* input) {
    if (input[0] == '-' && isint(input + 1)) { return 1; };
    if (input[0] == '\0') { return 0; };

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] < 48 || input[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int to_i_inner(char* input, int neg) {

    if (input[0] == '-') {
        return to_i_inner(input + 1, 1);
    }

    int output = 0;
    for (int i = 0; i < strlen(input); i++) {
        int placer = 1;
        for (int j = i; j < strlen(input) - 1; j++) { placer *= 10; };
        output += ((int)input[i] - 48) * placer;
    }

    if (neg) {
        return output - (output * 2);
    } else {
        return output;
    }
}

int to_i(char* input) {
    return to_i_inner(input, 0);
}


cell* categorize(char* c) {
    int builtinval = isbuiltin(c);
    if (builtinval) {
        int cell_value = (builtin_vals)builtinval - 1;
        return makecell(BUILTIN, (value){.builtin=cell_value}, &nil);
    } else if (isint(c)) {
        return makecell(INT, (value){.num=to_i(c)}, &nil);
    } else {
        return makecell(LABEL, (value){.label=c}, &nil);
    }
}

void debuglist(cell*);

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
        cell *quote = makecell(LABEL, (value){.builtin = QUOTE}, read(s, 0));
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
