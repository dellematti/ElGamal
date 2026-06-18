#include "ciphertext.h"

void ciphertext_init(CipherText *ct) {
    mpz_init(ct->xC1);
    mpz_init(ct->yC1);
    mpz_init(ct->xC2);
    mpz_init(ct->yC2);
}

void ciphertext_clear(CipherText *ct) {
    mpz_clear(ct->xC1);
    mpz_clear(ct->yC1);
    mpz_clear(ct->xC2);
    mpz_clear(ct->yC2);
}