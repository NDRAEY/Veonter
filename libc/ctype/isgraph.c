#include <stddef.h>
#include <stdbool.h>

int isgraph(int c) {
    return (c >= 33 && c <= 126);
}