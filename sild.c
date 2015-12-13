#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

int main() {

    /* char* test = "(hi (hi)) hi"; */
    char* test = "'(hi) 'hi";
    /* cell* list = read(&test); */
    cell* list = read(&test);
    debuglist(list);

    return 0;
}
