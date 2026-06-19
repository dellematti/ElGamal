#include "modSqrt.h"

// Restituisce in "out" una radice quadrata di a modulo p tramite Tonelli-Shanks.
// Se la radice esiste, restituisce 1. Altrimenti restituisce 0.
int modSqrt(mpz_t out, const mpz_t a, const mpz_t p) {
    mpz_set_ui(out, 0);

    if (mpz_cmp_ui(a, 0) == 0) {
        mpz_set_ui(out, 0);
        return 1;
    }

    if (mpz_cmp_ui(p, 2) == 0) {
        mpz_mod_ui(out, a, 2);
        return 1;
    }

    if (mpz_jacobi(a, p) != 1) {
        return 0;
    }

    mpz_t tmp, q, z, r, t, c, t2i, b;
    mpz_inits(tmp, q, z, r, t, c, t2i, b, NULL);

    // Caso veloce: p % 4 == 3
    mpz_mod_ui(tmp, p, 4);
    if (mpz_cmp_ui(tmp, 3) == 0) {
        mpz_add_ui(tmp, p, 1);
        mpz_fdiv_q_ui(tmp, tmp, 4);
        mpz_powm(out, a, tmp, p);
        mpz_clears(tmp, q, z, r, t, c, t2i, b, NULL);
        return 1;
    }

    // Scrive p - 1 = q * 2^s con q dispari
    mpz_sub_ui(q, p, 1);
    int s = 0;

    while (mpz_even_p(q)) {
        mpz_fdiv_q_ui(q, q, 2);
        s++;
    }

    // Cerca uno z tale che Jacobi(z, p) = -1
    mpz_set_ui(z, 2);
    while (mpz_jacobi(z, p) != -1) {
        mpz_add_ui(z, z, 1);
    }

    // Inizializzazione Tonelli-Shanks
    mpz_add_ui(tmp, q, 1);
    mpz_fdiv_q_ui(tmp, tmp, 2);
    mpz_powm(r, a, tmp, p);

    mpz_powm(t, a, q, p);
    mpz_powm(c, z, q, p);

    int m = s;

    while (mpz_cmp_ui(t, 1) != 0) {
        int i = 0;
        mpz_set(t2i, t);

        while (mpz_cmp_ui(t2i, 1) != 0 && i < m) {
            mpz_powm_ui(t2i, t2i, 2, p);
            i++;
        }

        if (i == m) {
            mpz_set_ui(out, 0);
            mpz_clears(tmp, q, z, r, t, c, t2i, b, NULL);
            return 0;
        }

        mpz_set_ui(tmp, 1);
        mpz_mul_2exp(tmp, tmp, m - i - 1);   // 2^(m-i-1)
        mpz_powm(b, c, tmp, p);

        mpz_powm_ui(c, b, 2, p);

        mpz_mul(r, r, b);
        mpz_mod(r, r, p);

        mpz_mul(t, t, c);
        mpz_mod(t, t, p);

        m = i;
    }

    mpz_set(out, r);
    mpz_clears(tmp, q, z, r, t, c, t2i, b, NULL);
    return 1;
}