# ElGamal Variant over Pell Conics in C

This project is a C implementation of a modified ElGamal cryptosystem based on Pell conics, using the GMP library for arbitrary-precision integer arithmetic.

> This is an experimental prototype. It has been improved for better API robustness and RNG handling, but it is not certified for production cryptographic use.

## Main features

The project includes:

- key generation
- encryption
- decryption
- conic group operations
- modular square root computation via Tonelli–Shanks
- big integer arithmetic with GMP
- benchmark programs for key generation, encryption, decryption, and full execution
- benchmark helper scripts for statistics and raw sample collection

## Project goal

The purpose of this project is educational and experimental.

It was developed to explore the implementation of a non-standard ElGamal-like cryptosystem over Pell conics, with particular attention to:

- translating mathematical definitions into C code
- handling arbitrary-precision arithmetic with GMP
- structuring a cryptographic project into multiple source files
- working with modular arithmetic and conic-based group operations

## Project structure

- `elGamalPell.c`  
  Main entry point of the program. Demonstrates key generation, encryption, and decryption.

- `gen.c` / `gen.h`  
  Key generation logic.

- `enc.c` / `enc.h`  
  Encryption logic.

- `dec.c` / `dec.h`  
  Decryption logic.

- `conicPow.c` / `conicPow.h`  
  Conic group operations and exponentiation on the Pell conic.

- `modSqrt.c` / `modSqrt.h`  
  Modular square root computation using the Tonelli–Shanks algorithm.

- `ciphertext.c` / `ciphertext.h`  
  Ciphertext data structure and memory management helpers.

- `keys.c` / `keys.h`  
  Key data structures and memory cleanup functions.

- `Makefile`  
  Build and benchmark automation.

## Benchmark structure

Benchmarks are stored in the `benchmark/` directory.

- `benchmark/benchmark.c`  
  Full pipeline benchmark: key generation + encryption + decryption

- `benchmark/benchmarkGen.c`  
  Key generation benchmark

- `benchmark/benchmarkEnc.c`  
  Encryption benchmark

- `benchmark/benchmarkDec.c`  
  Decryption benchmark

- `benchmark/benchmark_stats.sh`  
  Runs a benchmark multiple times and prints summary statistics

- `benchmark/benchmark_values.sh`  
  Runs a benchmark multiple times and saves raw timing samples to a file

## Requirements

To build this project, you need:

- GCC
- Make
- GMP

## Build

If GMP is already available in your environment, run:

```bash
make
```

## Test

Verify the example flow with:

```bash
make check
```
