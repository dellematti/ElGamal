#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../gen.h"
#include "../keys.h"

// Benchmark della sola key generation
// Uso:
//   ./benchmarkGen.out <key_length>
//
// Esempio:
//   ./benchmarkGen.out 512

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    char *endptr = NULL;
    long key_len_long = strtol(argv[1], &endptr, 10);
    if (*argv[1] == '\0' || *endptr != '\0' || key_len_long <= 0) {
        return 1;
    }

    int keyLen = (int)key_len_long;

    Keys k;
    keys_init(&k);

    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        return 1;
    }

    if (!gen(&k, keyLen)) {
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) {
        keys_clear(&k);
        return 1;
    }

    double elapsed = benchmark_time_diff(&start, &end);
    printf("%.6f\n", elapsed);

    keys_clear(&k);

    return 0;
}