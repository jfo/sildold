#include <stdio.h>
#include <stdlib.h>

#include "cell.c"
#include "reader.c"
#include "debugging.c"

int main() {

    char* test = "'() hi mom ()";
    cell* list = read(&test);
    debuglist(list);

    return 0;
}
