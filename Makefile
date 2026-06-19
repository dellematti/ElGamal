CC = gcc
CFLAGS = -O3 -Wall -Wextra -std=c11
DEBUGFLAGS = -O0 -g -Wall -Wextra -std=c11
LIBS = -lgmp

SRC = elGamalPell.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c
OUT = elGamalPell.out

BENCH_DIR = benchmark
BENCH_FULL_SRC = $(BENCH_DIR)/benchmark.c
BENCH_GEN_SRC = $(BENCH_DIR)/benchmarkGen.c
BENCH_ENC_SRC = $(BENCH_DIR)/benchmarkEnc.c
BENCH_DEC_SRC = $(BENCH_DIR)/benchmarkDec.c

BENCH_FULL_OUT = $(BENCH_DIR)/benchmark.out
BENCH_GEN_OUT = $(BENCH_DIR)/benchmarkGen.out
BENCH_ENC_OUT = $(BENCH_DIR)/benchmarkEnc.out
BENCH_DEC_OUT = $(BENCH_DIR)/benchmarkDec.out

.PHONY: all debug run check clean bench bench-gen bench-enc bench-dec bench-all

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(OUT)

debug:
	$(CC) $(DEBUGFLAGS) $(SRC) $(LIBS) -o $(OUT)

run: $(OUT)
	./$(OUT)

check: $(OUT)
	./$(OUT)

bench: $(BENCH_FULL_OUT)

bench-gen: $(BENCH_GEN_OUT)

bench-enc: $(BENCH_ENC_OUT)

bench-dec: $(BENCH_DEC_OUT)

bench-all: $(BENCH_FULL_OUT) $(BENCH_GEN_OUT) $(BENCH_ENC_OUT) $(BENCH_DEC_OUT)

$(BENCH_FULL_OUT): $(BENCH_FULL_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c
	$(CC) $(CFLAGS) $(BENCH_FULL_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c $(LIBS) -o $(BENCH_FULL_OUT)

$(BENCH_GEN_OUT): $(BENCH_GEN_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c gen.c enc.c dec.c random.c
	$(CC) $(CFLAGS) $(BENCH_GEN_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c gen.c enc.c dec.c random.c $(LIBS) -o $(BENCH_GEN_OUT)

$(BENCH_ENC_OUT): $(BENCH_ENC_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c
	$(CC) $(CFLAGS) $(BENCH_ENC_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c $(LIBS) -o $(BENCH_ENC_OUT)

$(BENCH_DEC_OUT): $(BENCH_DEC_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c
	$(CC) $(CFLAGS) $(BENCH_DEC_SRC) benchmark/benchmark_common.c ciphertext.c keys.c conicPow.c modSqrt.c gen.c enc.c dec.c random.c $(LIBS) -o $(BENCH_DEC_OUT)

clean:
	rm -f $(OUT) \
          $(BENCH_FULL_OUT) \
          $(BENCH_GEN_OUT) \
          $(BENCH_ENC_OUT) \
          $(BENCH_DEC_OUT)