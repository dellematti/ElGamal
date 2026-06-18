#ifndef DEC_H
#define DEC_H

#include <gmp.h>

#include "ciphertext.h"
#include "keys.h"

void funzioneDec(mpz_t output, CipherText ct, Keys keys);

#endif