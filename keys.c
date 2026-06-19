#include <gmp.h>
#include "keys.h"

void keys_init(Keys *keys) {
    mpz_inits(keys->pk.q, keys->pk.d,
              keys->pk.xG, keys->pk.yG,
              keys->pk.xH, keys->pk.yH,
              keys->sk.k,
              NULL);
}

void keys_clear(Keys *keys) {
    if (!keys) {
        return;
    }

    mpz_set_ui(keys->sk.k, 0);
    mpz_clears(keys->pk.q, keys->pk.d,
               keys->pk.xG, keys->pk.yG,
               keys->pk.xH, keys->pk.yH,
               keys->sk.k,
               NULL);
}