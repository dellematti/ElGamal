#ifndef ENC_H
#define ENC_H

#include <gmp.h>

#include "keys.h"
#include "ciphertext.h"

int enc(CipherText *ct, const mpz_t msg, const PublicKey *pk);

#endif