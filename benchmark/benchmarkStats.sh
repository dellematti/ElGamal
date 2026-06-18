#!/usr/bin/env bash

set -euo pipefail
export LC_ALL=C

usage() {
    echo "Usage: $0 <benchmark_binary> [iterations] [-- benchmark_args...]"
    echo
    echo "Examples:"
    echo "  $0 ./benchmarkDec.out 100"
    echo "  $0 ./benchmark.out 50 -- 2048"
    exit 1
}

if [ $# -lt 1 ]; then
    usage
fi

BENCH="$1"
shift

ITERATIONS=10
if [ $# -gt 0 ] && [[ "$1" =~ ^[0-9]+$ ]]; then
    ITERATIONS="$1"
    shift
fi

if [ $# -gt 0 ] && [ "$1" = "--" ]; then
    shift
fi

BENCH_ARGS=("$@")

if [ ! -x "$BENCH" ]; then
    echo "Error: '$BENCH' is not executable"
    exit 1
fi

TMP_FILE="$(mktemp)"
trap 'rm -f "$TMP_FILE"' EXIT

for ((i=1; i<=ITERATIONS; i++)); do
    VALUE="$("$BENCH" "${BENCH_ARGS[@]}" | tr -d '\r' | awk 'NF {print $1; exit}')"

    if ! awk -v x="$VALUE" 'BEGIN { exit !(x ~ /^[+-]?[0-9]+([.][0-9]+)?([eE][+-]?[0-9]+)?$/) }'; then
        echo "Error: benchmark output is not a valid numeric value: '$VALUE'"
        exit 1
    fi

    echo "$VALUE" >> "$TMP_FILE"
    printf "Run %d/%d: %s\n" "$i" "$ITERATIONS" "$VALUE"
done

printf "\n"

awk '
{
    x[NR] = $1
    sum += $1

    if (NR == 1 || $1 < min) min = $1
    if (NR == 1 || $1 > max) max = $1
}
END {
    n = NR
    mean = sum / n

    ss = 0
    for (i = 1; i <= n; i++) {
        d = x[i] - mean
        ss += d * d
    }

    pop_var = ss / n
    pop_std = sqrt(pop_var)

    samp_var = (n > 1) ? ss / (n - 1) : 0
    samp_std = sqrt(samp_var)

    printf("iterations = %d\n", n)
    printf("mean = %.6f seconds\n", mean)
    printf("min = %.6f seconds\n", min)
    printf("max = %.6f seconds\n", max)
    printf("population variance = %.6f\n", pop_var)
    printf("population standard deviation = %.6f\n", pop_std)

    if (n > 1) {
        printf("sample variance = %.6f\n", samp_var)
        printf("sample standard deviation = %.6f\n", samp_std)
    }
}
' "$TMP_FILE"