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

    char* t = "( cond (( eq ( quote  1 )( quote  2 ))( quote  first ))(( eq ( quote  1 )( quote  2 ))( quote  second )))";
    printf("%s\n", t);
    printlist(makelist(t));
    debuglist(makelist(t));
    printlist(makelist(t));
    return 0;
}
