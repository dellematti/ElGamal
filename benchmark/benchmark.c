#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

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

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    CipherText ct = enc(msg, k.pk);

    mpz_t risultato;
    mpz_init(risultato);
    funzioneDec(risultato, ct, k);

    clock_t end = clock();

    if (mpz_cmp(msg, risultato) != 0) {
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return 1;
    }

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%.6f\n", elapsed);

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);
    mpz_clear(risultato);

    return 0;
}
