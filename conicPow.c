#include "conicPow.h"

// Nei parametri out1 e out2 viene salvato il risultato dell'operazione.
void conic_op(mpz_t out1, mpz_t out2,
              const mpz_t x1, const mpz_t y1,
              const mpz_t x2, const mpz_t y2,
              const mpz_t d, const mpz_t n) {

    mpz_t tmp, tmp2;
    mpz_inits(tmp, tmp2, NULL);

    mpz_mul(tmp, x1, x2);
    mpz_mul(tmp2, y1, y2);
    mpz_mul(tmp2, tmp2, d);
    mpz_add(out1, tmp, tmp2);
    mpz_mod(out1, out1, n);

    mpz_mul(tmp, x1, y2);
    mpz_mul(tmp2, y1, x2);
    mpz_add(out2, tmp, tmp2);
    mpz_mod(out2, out2, n);

    mpz_clears(tmp, tmp2, NULL);
}

// Nei parametri res1 e res2 viene salvato il risultato dell'esponenziazione.
// I parametri res1 e res2 devono essere già inizializzati.
void conic_pow(mpz_t res1, mpz_t res2,
               const mpz_t xG, const mpz_t yG,
               const mpz_t e, const mpz_t d, const mpz_t n) {

    mpz_set_ui(res1, 1);
    mpz_set_ui(res2, 0);

    if (mpz_sgn(e) == 0) {
        return;
    }

    mp_bitcnt_t bitlen = mpz_sizeinbase(e, 2);

    mpz_t out1, out2;
    mpz_inits(out1, out2, NULL);

    for (mp_bitcnt_t i = bitlen; i > 0; --i) {
        // square
        conic_op(out1, out2, res1, res2, res1, res2, d, n);
        mpz_set(res1, out1);
        mpz_set(res2, out2);

        // multiply by generator if current bit is 1
        if (mpz_tstbit(e, i - 1)) {
            conic_op(out1, out2, res1, res2, xG, yG, d, n);
            mpz_set(res1, out1);
            mpz_set(res2, out2);
        }
    }

    mpz_clears(out1, out2, NULL);
}