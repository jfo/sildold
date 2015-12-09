#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

int main() {
    debuglist(makelist("'(hi 'hi )"));
    return 0;
}
