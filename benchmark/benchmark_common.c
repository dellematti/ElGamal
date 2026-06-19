#define _POSIX_C_SOURCE 200809L

#include "benchmark_common.h"
#include <stdlib.h>
#include <string.h>

bool parse_key_length(int argc, char *argv[], int *keyLen) {
    if (argc < 2 || !argv[1] || !keyLen) {
        return false;
    }

    char *endptr = NULL;
    long value = strtol(argv[1], &endptr, 10);
    if (*argv[1] == '\0' || *endptr != '\0' || value <= 0) {
        return false;
    }

    *keyLen = (int)value;
    return true;
}

double benchmark_time_diff(const struct timespec *start, const struct timespec *end) {
    double sec = (double)(end->tv_sec - start->tv_sec);
    double nsec = (double)(end->tv_nsec - start->tv_nsec);
    return sec + nsec * 1e-9;
}
