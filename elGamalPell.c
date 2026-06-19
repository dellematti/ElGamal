#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "ciphertext.h"
#include "dec.h"
#include "enc.h"
#include "gen.h"
#include "keys.h"

int main(void) {
    Keys k;
    keys_init(&k);
    if (!gen(&k, 512)) {
        fprintf(stderr, "Key generation failed\n");
        return EXIT_FAILURE;
    }

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    printf("\nMessaggio iniziale:\n");
    mpz_out_str(stdout, 10, msg);
    printf("\n\n");

    CipherText ct;
    if (!enc(&ct, msg, &k.pk)) {
        fprintf(stderr, "Encryption failed\n");
        keys_clear(&k);
        mpz_clear(msg);
        return EXIT_FAILURE;
    }

    printf("Messaggio cifrato:\n");
    mpz_out_str(stdout, 16, ct.xC1);
    printf("\n");
    mpz_out_str(stdout, 16, ct.yC1);
    printf("\n");
    mpz_out_str(stdout, 16, ct.xC2);
    printf("\n");
    mpz_out_str(stdout, 16, ct.yC2);
    printf("\n");

    mpz_t risultato;
    mpz_init(risultato);
    if (!decrypt(risultato, &ct, &k)) {
        fprintf(stderr, "Decryption failed\n");
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(risultato);
        return EXIT_FAILURE;
    }

    printf("\nMessaggio decifrato:\n");
    mpz_out_str(stdout, 10, risultato);
    printf("\n");

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);
    mpz_clear(risultato);

    return EXIT_SUCCESS;
}
