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

    clock_t start = clock();

    Keys k = gen(keyLen);

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%.6f\n", elapsed);

    keys_clear(&k);

    return 0;
}