#ifndef SIEVE_GEOMETER_PATTERN
#define SIEVE_GEOMETER_PATTERN

#include "common_types.h"

/*
u16 encoded_patterns[16] = {
    0x2057, // (2, 0, 5, 7)
    0x2024, // (2, 0, 2, 4)
    0x0055, // (0, 0, 5, 5)
    0x0022, // (0, 0, 2, 2)
    0x0235, // (0, 2, 3, 5)
    0x0202, // (0, 2, 0, 2)
    0x2002, // (2, 0, 0, 2)
    0x0011, // (0, 0, 1, 1)
    0x2035, // (2, 0, 3, 5)
    0x2046, // (2, 0, 4, 6)
    0x0000, // (0, 0, 0, 0)
    0x0033, // (0, 0, 3, 3)
    0x2013, // (2, 0, 1, 3)
    0x0213, // (0, 2, 1, 3)
    0x0044, // (0, 0, 4, 4)
    0x0246  // (0, 2, 4, 6)
};
*/

typedef struct {
    s8 grammarSeed;
    u8 cMod10;
    u8 pyramid;
    u8 modPyramid;
    u8 csMod6;
    u8 comp;
} Candidate;

Candidate getCandidate(u64 previous, u64 current);
void emitCandidateCSVHeader(FILE* out);
void emitCandidateCSVRow(FILE* out, u64 previous, u64 current, u8 isPrime, Candidate c); 

#endif
