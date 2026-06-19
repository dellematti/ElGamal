#include <gmp.h>

#include "dec.h"
#include "conicPow.h"

int decrypt(mpz_t output, const CipherText *ct, const Keys *keys) {
    if (!output || !ct || !keys) {
        return 0;
    }

    mp_bitcnt_t n = mpz_sizeinbase(keys->pk.q, 2);
    mp_bitcnt_t var = n / 16;

    mpz_t xF, yF, tmp, M1, M2;
    mpz_inits(xF, yF, tmp, M1, M2, NULL);

    conic_pow(xF, yF, ct->xC1, ct->yC1, keys->sk.k, keys->pk.d, keys->pk.q);

    mpz_neg(tmp, yF);
    mpz_mod(tmp, tmp, keys->pk.q);

    conic_op(M1, M2, xF, tmp, ct->xC2, ct->yC2, keys->pk.d, keys->pk.q);
    mpz_fdiv_q_2exp(output, M2, var);

    mpz_clears(xF, yF, tmp, M1, M2, NULL);
    return 1;
}