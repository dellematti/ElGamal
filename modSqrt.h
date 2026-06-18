#ifndef MODSQRT_H
#define MODSQRT_H

#include <gmp.h>

// Restituisce in "out" una radice quadrata di a modulo p.
// Se non esiste, la funzione lascia out a 0 oppure comunque
// non garantisce un valore valido a seconda dell'implementazione.
// In futuro si potrebbe migliorare facendo ritornare un int
// per indicare successo/fallimento.
void modSqrt(mpz_t out, const mpz_t a, const mpz_t p);

#endif