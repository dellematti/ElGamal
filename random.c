#include "random.h"

#include <fcntl.h>
#include <gmp.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static int os_random_bytes(void *buf, size_t len) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        return 0;
    }

    unsigned char *bytes = buf;
    size_t total = 0;
    while (total < len) {
        ssize_t n = read(fd, bytes + total, len - total);
        if (n <= 0) {
            close(fd);
            return 0;
        }
        total += (size_t)n;
    }

    close(fd);
    return 1;
}

int secure_seed_randstate(gmp_randstate_t *state) {
    if (!state) {
        return 0;
    }

    unsigned char seed_bytes[64];
    if (!os_random_bytes(seed_bytes, sizeof(seed_bytes))) {
        return 0;
    }

    mpz_t seed;
    mpz_init(seed);
    mpz_import(seed, sizeof(seed_bytes), 1, 1, 0, 0, seed_bytes);

    gmp_randinit_default(*state);
    gmp_randseed(*state, seed);

    mpz_clear(seed);
    return 1;
}
