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
    dict->next = delete_entry(label, dict->next);
    return dict;
}

int main() {
    entry *first = create_entry( "first", "first value", NULL );
    entry *second = create_entry( "second", "second value", first );
    entry *third = create_entry( "third", "third value", second );
    entry *fourth = create_entry( "fourth", "fourth value", third );

    printf("%s\n", read_entry("first", fourth));
    printf("%s\n", read_entry("second", fourth));
    printf("%s\n", read_entry("third", fourth));
    printf("%s\n", read_entry("fourth", fourth));
    printf("%s\n", read_entry("not a real value", fourth));
    printf("\n");

    delete_entry("second", fourth);

    printf("%s\n", read_entry("first", fourth));
    printf("%s\n", read_entry("second", fourth));
    printf("%s\n", read_entry("third", fourth));
    printf("%s\n", read_entry("fourth", fourth));
    printf("%s\n", read_entry("not a value", fourth));

    delete_entry("second", fourth);

    return 0;
}
