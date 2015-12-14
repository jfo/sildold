#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"
#include "builtins.c"

int main() {

    char* test = "((#t 6))";
    cell* list = read(&test);
    debuglist(cond(list));

    return 0;
}
