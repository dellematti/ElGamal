#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "benchmark_common.h"
#include "../gen.h"
#include "../enc.h"
#include "../dec.h"
#include "../ciphertext.h"
#include "../keys.h"

// Benchmark completo: key generation + encryption + decryption
// Uso:
//   ./benchmark.out <key_length>
//
// Esempio:
//   ./benchmark.out 512

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

    mpz_t risultato;
    mpz_init(risultato);

    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return 1;
    }

    if (!enc(&ct, msg, &k.pk) || !decrypt(risultato, &ct, &k)) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return 1;
    }

    if (mpz_cmp(msg, risultato) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return 1;
    }

    double elapsed = benchmark_time_diff(&start, &end);
    printf("%.6f\n", elapsed);

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);
    mpz_clear(risultato);

    return 0;
}
