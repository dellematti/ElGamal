#ifndef CONICPOW_H
#define CONICPOW_H

#include <gmp.h>

void conic_op(mpz_t out1, mpz_t out2,
              const mpz_t x1, const mpz_t y1,
              const mpz_t x2, const mpz_t y2,
              const mpz_t d, const mpz_t n);

void conic_pow(mpz_t res1, mpz_t res2,
               const mpz_t xG, const mpz_t yG,
               const mpz_t e, const mpz_t d, const mpz_t n);

#endif