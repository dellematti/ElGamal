#ifndef RANDOM_H
#define RANDOM_H

#include <gmp.h>
#include <stddef.h>

// Seeds a GMP random state using OS entropy from /dev/urandom.
// Returns 1 on success, 0 on failure.
int secure_seed_randstate(gmp_randstate_t *state);

#endif
