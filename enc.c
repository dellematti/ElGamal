#include <gmp.h>
#include <stdlib.h>

#include "enc.h"
#include "keys.h"
#include "ciphertext.h"
#include "conicPow.h"
#include "modSqrt.h"
#include "random.h"

// Cifra il messaggio 'msg' utilizzando la chiave pubblica.
// Il ciphertext viene inizializzato e memorizzato in ct.
int enc(CipherText *ct, const mpz_t msg, const PublicKey *pk) {
    if (!ct || !pk) {
        return 0;
    }

    ciphertext_init(ct);

    mp_bitcnt_t n = mpz_sizeinbase(pk->q, 2);
    mp_bitcnt_t var = n / 16;

    mpz_t y, stop, v, square, x;
    mpz_inits(y, stop, v, square, x, NULL);

    mpz_mul_2exp(y, msg, var);
    mpz_set_ui(stop, 1);
    mpz_mul_2exp(stop, stop, var);
    mpz_set_ui(v, 0);

    int found = 0;
    while (mpz_cmp(v, stop) < 0) {
        mpz_mul(square, y, y);
        mpz_mod(square, square, pk->q);
        mpz_mul(square, square, pk->d);
        mpz_add_ui(square, square, 1);
        mpz_mod(square, square, pk->q);

        if (mpz_jacobi(square, pk->q) == 1) {
            found = 1;
            break;
        }

        mpz_add_ui(y, y, 1);
        mpz_add_ui(v, v, 1);
    }

    if (!found) {
        mpz_set_ui(y, 0);
        mpz_set_ui(square, 0);
        mpz_set_ui(x, 0);
        mpz_clears(y, stop, v, square, x, NULL);
        ciphertext_clear(ct);
        return 0;
    }

    if (!modSqrt(x, square, pk->q)) {
        mpz_set_ui(y, 0);
        mpz_set_ui(square, 0);
        mpz_set_ui(x, 0);
        mpz_clears(y, stop, v, square, x, NULL);
        ciphertext_clear(ct);
        return 0;
    }

    mpz_t r, tmpMax;
    mpz_inits(r, tmpMax, NULL);

    gmp_randstate_t state;
    if (!secure_seed_randstate(&state)) {
        mpz_set_ui(y, 0);
        mpz_set_ui(square, 0);
        mpz_set_ui(x, 0);
        mpz_set_ui(r, 0);
        mpz_set_ui(tmpMax, 0);
        mpz_clears(y, stop, v, square, x, r, tmpMax, NULL);
        ciphertext_clear(ct);
        return 0;
    }

    mpz_sub_ui(tmpMax, pk->q, 2);
    mpz_urandomm(r, state, tmpMax);
    mpz_add_ui(r, r, 2);

    mpz_t xC1, yC1, F1, F2, xC2, yC2;
    mpz_inits(xC1, yC1, F1, F2, xC2, yC2, NULL);

    conic_pow(xC1, yC1, pk->xG, pk->yG, r, pk->d, pk->q);
    conic_pow(F1, F2, pk->xH, pk->yH, r, pk->d, pk->q);
    conic_op(xC2, yC2, F1, F2, x, y, pk->d, pk->q);

    mpz_set(ct->xC1, xC1);
    mpz_set(ct->yC1, yC1);
    mpz_set(ct->xC2, xC2);
    mpz_set(ct->yC2, yC2);

    mpz_set_ui(y, 0);
    mpz_set_ui(square, 0);
    mpz_set_ui(x, 0);
    mpz_set_ui(r, 0);
    mpz_set_ui(tmpMax, 0);
    mpz_clears(y, stop, v, square, x,
               r, tmpMax, xC1, yC1, F1, F2, xC2, yC2,
               NULL);
    gmp_randclear(state);

    return 1;
}