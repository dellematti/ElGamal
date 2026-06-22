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
    // 512-bit keys are used for example purposes and fast execution.
    // Not intended as a production security parameter.
    // Other possible values are 1024, 1536, 3840, and 7680.
    if (!gen(&k, 512)) {
        fprintf(stderr, "Key generation failed\n");
        return EXIT_FAILURE;
    }

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    printf("\nOriginal message:\n");
    mpz_out_str(stdout, 10, msg);
    printf("\n\n");

    CipherText ct;
    if (!enc(&ct, msg, &k.pk)) {
        fprintf(stderr, "Encryption failed\n");
        keys_clear(&k);
        mpz_clear(msg);
        return EXIT_FAILURE;
    }

    printf("Ciphertext:\n");
    mpz_out_str(stdout, 16, ct.xC1);
    printf("\n");
    mpz_out_str(stdout, 16, ct.yC1);
    printf("\n");
    mpz_out_str(stdout, 16, ct.xC2);
    printf("\n");
    mpz_out_str(stdout, 16, ct.yC2);
    printf("\n");

    mpz_t decrypted_msg;
    mpz_init(decrypted_msg);
    if (!decrypt(decrypted_msg, &ct, &k)) {
        fprintf(stderr, "Decryption failed\n");
        ciphertext_clear(&ct);
        keys_clear(&k);
        mpz_clear(msg);
        mpz_clear(decrypted_msg);
        return EXIT_FAILURE;
    }

    printf("\nDecrypted message:\n");
    mpz_out_str(stdout, 10, decrypted_msg);
    printf("\n");

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);
    mpz_clear(decrypted_msg);

    return EXIT_SUCCESS;
}
