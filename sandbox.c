#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

int isint(char* input) {
    if (input[0] == '-') { return isint(input + 1); };
    if (input[0] == '\0') { return 0; };

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] < 48 || input[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int to_i_inner(char* input, int neg) {

    if (input[0] == '-') {
        return to_i_inner(input + 1, 1);
    }

    int output = 0;
    for (int i = 0; i < strlen(input); i++) {
        int placer = 1;
        for (int j = i; j < strlen(input) - 1; j++) { placer *= 10; };
        output += ((int)input[i] - 48) * placer;
    }

    if (neg) {
        return output - (output * 2);
    } else {
        return output;
    }
}

int to_i(char* input) {
    return to_i_inner(input, 0);
}


int main() {

    /* printf("%i", to_i("-1112870", 0)); */
    printf("%i", isint("-"));
    return 0;
}
