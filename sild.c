#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

int main() {
    /* debuglist(makelist("'(jdsio '1)")); */
    /* debuglist(makelist("'(thing)")); */
    /* debuglist(makelist("'hi")); */
    /* debuglist(makelist("('hi)")); */

    char *thing = "(this is a test)";

    char **pointer_to_thing = &thing;

    /* debuglist(makelist(thing)); */
    /* debuglist(makelist(*pointer_to_thing)); */

    /* printf("%c\n", ***pointer_to_thing); */
    printf("%c\n", **pointer_to_thing);
    printf("\n");

    printf("%s\n", *pointer_to_thing);

    *pointer_to_thing += 1;

    printf("%s\n", *pointer_to_thing);
    printf("%p\n", *pointer_to_thing);
    printf("\n");

    printf("%p\n", pointer_to_thing);
    printf("%p\n", &pointer_to_thing);
    printf("\n");


    /* char* t = "( cond (( eq ( quote  1 )( quote  2 ))( quote  first ))(( eq ( quote  1 )( quote  2 ))( quote  second )))"; */
    /* printf("%s\n", t); */
    /* printlist(makelist(t)); */
    /* debuglist(makelist(t)); */
    /* printlist(makelist(t)); */
    return 0;
}
