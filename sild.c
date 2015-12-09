#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

int main() {
    debuglist(makelist("'(jdsio '1)"));
    debuglist(makelist("'(thing)"));
    debuglist(makelist("'hi"));
    debuglist(makelist("('hi)"));
    return 0;
}
