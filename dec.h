#ifndef DEC_H
#define DEC_H

#include <gmp.h>

#include "ciphertext.h"
#include "keys.h"

int decrypt(mpz_t output, const CipherText *ct, const Keys *keys);

#endif