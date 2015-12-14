#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

int main() {

    /* char* test = "((that 7) (this 6))"; */
    char* test = "((this 6) (that x) (tat thing))";
    cell* list = read(&test);
    debuglist(assoc("tat", list));

    return 0;
}
