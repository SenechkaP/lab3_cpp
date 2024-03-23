#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"

int check_str(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

long check_int(char *input) {
    long result;
    char *endptr;

    result = strtol(input, &endptr, 10);

    if (*endptr != '\0') {
        return -1;
    }
    return result;
}
