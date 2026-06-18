#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

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
    if (argc < 2) {
        return 1;
    }

    char *endptr = NULL;
    long key_len_long = strtol(argv[1], &endptr, 10);
    if (*argv[1] == '\0' || *endptr != '\0' || key_len_long <= 0) {
        return 1;
    }

    int keyLen = (int)key_len_long;

    Keys k = gen(keyLen);

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    clock_t start = clock();

    CipherText ct = enc(msg, k.pk);

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%.6f\n", elapsed);

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);

    return 0;
}
``