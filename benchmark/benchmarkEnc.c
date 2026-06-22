#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "benchmark_common.h"
#include "../gen.h"
#include "../enc.h"
#include "../ciphertext.h"
#include "../keys.h"

// Benchmark della sola encryption
// Uso:
//   ./benchmarkEnc.out <key_length>
//
// Esempio:
//   ./benchmarkEnc.out 512

int main(int argc, char *argv[]) {
    int keyLen;
    if (!parse_key_length(argc, argv, &keyLen)) {
        return 1;
    }

    Keys k;
    keys_init(&k);
    if (!gen(&k, keyLen)) {
        return 1;
    }

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    CipherText ct;
    ciphertext_init(&ct);

    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        return 1;
    }

    if (!enc(&ct, msg, &k.pk)) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        return 1;
    }

    double elapsed = benchmark_time_diff(&start, &end);
    printf("%.6f\n", elapsed);

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);

    return 0;
}
