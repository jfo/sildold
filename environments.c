#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct env {
    char *label;
    char *value;
    struct env *next;
} env;

env *create_entry(char *label, char *value, env *dict) {
    env *out = malloc(sizeof(env));
    out->label = label;
    out->value = value;
    out->next = dict;
    return out;
}

char *read_entry(char *label, env *dict) {
    if (strcmp(label, dict->label) == 0) {
        return dict->value;
    } else if (dict->next) {
        return read_entry(label, dict->next);
    }
    return NULL;
}

env *delete_entry(char *label, env *dict) {
    if (strcmp(label, dict->label) == 0) {
        free(dict);
        return dict->next;
    }
    if (dict->next != NULL) { dict->next = delete_entry(label, dict->next); }
    return dict;
}
