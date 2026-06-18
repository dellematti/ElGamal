#ifndef KEYS_H
#define KEYS_H

typedef struct {
    char *q;
    char *d;
    char *xG;
    char *yG;
    char *xH;
    char *yH;
} PublicKey;

typedef struct {
    char *k;
} SecretKey;

typedef struct {
    PublicKey pk;
    SecretKey sk;
} Keys;

void keys_clear(Keys *keys);

#endif