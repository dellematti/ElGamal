#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <gmp.h>

typedef struct {
    mpz_t xC1;
    mpz_t yC1;
    mpz_t xC2;
    mpz_t yC2;
} CipherText;

void ciphertext_init(CipherText *ct);
void ciphertext_clear(CipherText *ct);

#endif