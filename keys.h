#ifndef KEYS_H
#define KEYS_H

#include <gmp.h>

typedef struct {
    mpz_t q;
    mpz_t d;
    mpz_t xG;
    mpz_t yG;
    mpz_t xH;
    mpz_t yH;
} PublicKey;

typedef struct {
    mpz_t k;
} SecretKey;

typedef struct {
    PublicKey pk;
    SecretKey sk;
} Keys;

void keys_init(Keys *keys);
void keys_clear(Keys *keys);

#endif