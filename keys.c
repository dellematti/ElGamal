#include <stdlib.h>
#include "keys.h"

void keys_clear(Keys *keys) {
    free(keys->pk.q);
    free(keys->pk.d);
    free(keys->pk.xG);
    free(keys->pk.yG);
    free(keys->pk.xH);
    free(keys->pk.yH);
    free(keys->sk.k);

    keys->pk.q = NULL;
    keys->pk.d = NULL;
    keys->pk.xG = NULL;
    keys->pk.yG = NULL;
    keys->pk.xH = NULL;
    keys->pk.yH = NULL;
    keys->sk.k = NULL;
}