#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "keys.h"
#include "ciphertext.h"

Keys gen(int n);
CipherText enc(const mpz_t msg, PublicKey pk);
void funzioneDec(mpz_t output, CipherText ct, Keys keys);

// Compilazione consigliata:
// gcc elGamalPell.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c -lgmp -O3 -o elGamalPell.out
//
// Esecuzione:
// ./elGamalPell.out

int main(void) {
    Keys k = gen(512);

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);

    printf("\nMessaggio iniziale:\n");
    mpz_out_str(stdout, 10, msg);
    printf("\n\n");

    CipherText ct = enc(msg, k.pk);

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
    funzioneDec(risultato, ct, k);

    printf("\nMessaggio decifrato:\n");
    mpz_out_str(stdout, 10, risultato);
    printf("\n");

    ciphertext_clear(&ct);
    keys_clear(&k);
    mpz_clear(msg);
    mpz_clear(risultato);

    return EXIT_SUCCESS;
}
