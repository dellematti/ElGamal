# ElGamal over Pell Conics in C

This project is a C implementation of an ElGamal-style cryptosystem built on Pell conics, utilizing the GNU Multiple Precision Arithmetic Library (GMP) for arbitrary-precision integer arithmetic. The codebase is directly inspired by recent academic research in conic-based cryptography, detailed in the accompanying `REFERENCES.md` file.

## Project overview

This project implements a public-key scheme based on Pell conic arithmetic, with an emphasis on:

- translating mathematical group operations into production-ready C code
- separating core cryptographic logic from utility and benchmark code
- using GMP for reliable large-integer handling
- measuring performance with dedicated benchmark executables
- keeping the implementation compact and reusable for study or prototyping

## What is included

- modular C11 codebase with separate key generation, encryption, decryption, and conic arithmetic
- GMP-based multi-precision arithmetic for large integer operations
- secure randomness seeded from the operating system
- benchmark suite for key generation, encryption, decryption, and full workflows
- `Makefile` with `make`, `make check`, and dedicated benchmark targets

## Repository structure

- `elGamalPell.c` — example program demonstrating key generation, encryption, and decryption. The sample main currently uses a fixed 512-bit key size and a short message for demonstration and fast execution.
- `gen.c` / `gen.h` — key generation logic for the Pell conic ElGamal variant.
- `enc.c` / `enc.h` — encryption implementation.
- `dec.c` / `dec.h` — decryption implementation.
- `conicPow.c` / `conicPow.h` — Pell conic exponentiation and group operations.
- `modSqrt.c` / `modSqrt.h` — modular square root implementation using Tonelli–Shanks.
- `ciphertext.c` / `ciphertext.h` — ciphertext representation and helper functions.
- `keys.c` / `keys.h` — public/secret key structures and memory cleanup.
- `random.c` / `random.h` — secure RNG seeding from OS entropy.
- `Makefile` — build, test, and benchmark targets.
- `benchmark/` — suite of benchmark programs and helpers.

## Build and run

To build and run this project locally, you will need:
- A C compiler (`gcc` or `clang`) with C11 support.
- The `make` build utility.
- GMP development libraries (`libgmp-dev` on Debian/Ubuntu, `gmp-devel` on Fedora) installed via your package manager.

Build the main program with:  

```bash
make
```

Run the example demo:

```bash
./elGamalPell.out
```

Compile and run the project in a single step:
```bash
make run
```

Verify the execution target:

```bash
make check
```

## Benchmarks

Build all the benchmark utilities (generation, encryption, decryption, and full workflow) at once:

```bash
make bench-all
```

Run a specific benchmark executable by passing the desired bit-length for the prime (e.g., 512 bits for encryption):

```bash
./benchmark/benchmarkEnc.out 512
```

## Disclaimer

> Experimental prototype for research and learning. Not audited for production cryptographic use.

