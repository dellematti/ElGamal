#include "dec.h"
#include "conicPow.h"


void funzioneDec(mpz_t output, CipherText ct, Keys keys) {
    mpz_t q, d, k;
    mpz_inits(q, d, k, NULL);

    mpz_set_str(q, keys.pk.q, 16);
    mpz_set_str(d, keys.pk.d, 16);
    mpz_set_str(k, keys.sk.k, 16);

    mp_bitcnt_t n = mpz_sizeinbase(q, 2);
    mp_bitcnt_t var = n / 16;

    mpz_t xF, yF;
    mpz_inits(xF, yF, NULL);

    conic_pow(xF, yF, ct.xC1, ct.yC1, k, d, q);

    mpz_t tmp;
    mpz_init(tmp);
    mpz_neg(tmp, yF);
    mpz_mod(tmp, tmp, q);

    mpz_t M1, M2;
    mpz_inits(M1, M2, NULL);

    conic_op(M1, M2, xF, tmp, ct.xC2, ct.yC2, d, q);

    mpz_fdiv_q_2exp(output, M2, var);

    mpz_clears(q, d, k, xF, yF, tmp, M1, M2, NULL);
}