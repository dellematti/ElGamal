#ifndef MODSQRT_H
#define MODSQRT_H

#include <gmp.h>

// Compute a modular square root of a modulo p using Tonelli-Shanks.
// Returns 1 if the square root exists and is written to out, 0 otherwise.
int modSqrt(mpz_t out, const mpz_t a, const mpz_t p);

#endif