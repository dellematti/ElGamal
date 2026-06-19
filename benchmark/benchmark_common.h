#ifndef BENCHMARK_COMMON_H
#define BENCHMARK_COMMON_H

#include <gmp.h>
#include <stdbool.h>
#include <time.h>

bool parse_key_length(int argc, char *argv[], int *keyLen);
double benchmark_time_diff(const struct timespec *start, const struct timespec *end);

#endif