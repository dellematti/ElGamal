#ifndef ENC_H
#define ENC_H

#include <gmp.h>

#include "keys.h"
#include "ciphertext.h"

CipherText enc(const mpz_t msg, PublicKey pk);

#endif