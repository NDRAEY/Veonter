#include <stddef.h>
#include <stdbool.h>

int isprint(int c) {
    return (c >= 32 && c <= 126);
}