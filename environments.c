#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
    char *label;
    char *value;
    struct entry *next;
} entry;

entry *create_entry(char *label, char *value, entry *dict) {
    entry *out = malloc(sizeof(entry));
    out->label = label;
    out->value = value;
    out->next = dict;
    return out;
}

char *read_entry(char *label, entry *dict) {
    if (strcmp(label, dict->label) == 0) {
        return dict->value;
    } else if (dict->next) {
        return read_entry(label, dict->next);
    }
    return NULL;
}

entry *delete_entry(char *label, entry *dict) {
    if (strcmp(label, dict->label) == 0) {
        free(dict);
        return dict->next;
    }
    if (dict->next != NULL) { dict->next = delete_entry(label, dict->next); }
    return dict;
}

int main() {
    return 0;
}
