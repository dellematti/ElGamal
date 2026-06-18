#!/usr/bin/env bash

set -euo pipefail
export LC_ALL=C

usage() {
    echo "Usage: $0 <benchmark_binary> <output_file> [iterations] [-- benchmark_args...]"
    echo
    echo "Examples:"
    echo "  $0 ./benchmarkEnc.out enc_times.txt 100"
    echo "  $0 ./benchmark.out full_2048.txt 50 -- 2048"
    exit 1
}

if [ $# -lt 2 ]; then
    usage
fi

BENCH="$1"
OUTPUT_FILE="$2"
shift 2

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

: > "$OUTPUT_FILE"

for ((i=1; i<=ITERATIONS; i++)); do
    VALUE="$("$BENCH" "${BENCH_ARGS[@]}" | tr -d '\r' | awk 'NF {print $1; exit}')"

    if ! awk -v x="$VALUE" 'BEGIN { exit !(x ~ /^[+-]?[0-9]+([.][0-9]+)?([eE][+-]?[0-9]+)?$/) }'; then
        echo "Error: benchmark output is not a valid numeric value: '$VALUE'"
        exit 1
    fi

    echo "$VALUE" >> "$OUTPUT_FILE"
    printf "Run %d/%d: %s\n" "$i" "$ITERATIONS" "$VALUE"
done

printf "\nSaved %d samples to %s\n" "$ITERATIONS" "$OUTPUT_FILE"