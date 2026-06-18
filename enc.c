#include <time.h>
#include <gmp.h>

#include "enc.h"
#include "keys.h"
#include "ciphertext.h"
#include "conicPow.h"
#include "modSqrt.h"


// Cifra il messaggio 'msg' utilizzando la chiave pubblica.
CipherText enc(const mpz_t msg, PublicKey pk) {
    mpz_t q, d, xG, yG, xH, yH;
    mpz_inits(q, d, xG, yG, xH, yH, NULL);

    mpz_set_str(q, pk.q, 16);
    mpz_set_str(d, pk.d, 16);
    mpz_set_str(xG, pk.xG, 16);
    mpz_set_str(yG, pk.yG, 16);
    mpz_set_str(xH, pk.xH, 16);
    mpz_set_str(yH, pk.yH, 16);

    mp_bitcnt_t n = mpz_sizeinbase(q, 2);
    mp_bitcnt_t var = n / 16;

    // RNG solo per test/demo: non sicuro per uso crittografico reale
    long seed = (long)time(NULL) ^ (long)clock();
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, (unsigned long)seed);

    mpz_t y, stop, v, square, x;
    mpz_inits(y, stop, v, square, x, NULL);

    mpz_mul_2exp(y, msg, var);

    mpz_set_ui(stop, 1);
    mpz_mul_2exp(stop, stop, var);

    mpz_set_ui(v, 0);

    int found = 0;
    while (mpz_cmp(v, stop) < 0) {
        // square = (1 + d * y^2) mod q
        mpz_mul(square, y, y);
        mpz_mod(square, square, q);
        mpz_mul(square, square, d);
        mpz_add_ui(square, square, 1);
        mpz_mod(square, square, q);

        if (mpz_jacobi(square, q) == 1) {
            found = 1;
            break;
        }

        mpz_add_ui(y, y, 1);
        mpz_add_ui(v, v, 1);
    }

    CipherText ct;
    ciphertext_init(&ct);

    if (!found) {
        mpz_clears(q, d, xG, yG, xH, yH, y, stop, v, square, x, NULL);
        gmp_randclear(state);
        return ct;
    }

    modSqrt(x, square, q);

    mpz_t r, tmpMax;
    mpz_inits(r, tmpMax, NULL);

    // r in [2, q]
    mpz_sub_ui(tmpMax, q, 1);
    mpz_urandomm(r, state, tmpMax);
    mpz_add_ui(r, r, 2);

    mpz_t xC1, yC1, F1, F2, xC2, yC2;
    mpz_inits(xC1, yC1, F1, F2, xC2, yC2, NULL);

    conic_pow(xC1, yC1, xG, yG, r, d, q);
    conic_pow(F1, F2, xH, yH, r, d, q);
    conic_op(xC2, yC2, F1, F2, x, y, d, q);

    mpz_set(ct.xC1, xC1);
    mpz_set(ct.yC1, yC1);
    mpz_set(ct.xC2, xC2);
    mpz_set(ct.yC2, yC2);

    mpz_clears(q, d, xG, yG, xH, yH, y, stop, v, square, x,
               r, tmpMax, xC1, yC1, F1, F2, xC2, yC2, NULL);
    gmp_randclear(state);

    return ct;
}