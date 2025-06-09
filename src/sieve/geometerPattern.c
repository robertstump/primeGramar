#include "geometerPattern.h"
#include <stdio.h>

static const u8 squareMod10[10] = { 0, 1, 0, 9, 0, 0, 0, 9, 0, 1 };

Candidate getCandidate(u64 previous, u64 current) {
    Candidate new;

    u8 bSqr = squareMod10[current % 10];
    u8 aSqr = squareMod10[previous % 10];

    u64 aSqrNoM = previous * previous;
    u64 bSqrNoM = current * current;

    u64 bPyr = (bSqrNoM) / 3;
    u64 aPyr = (aSqrNoM) / 3; 
    
    u8 pyr = (bPyr > aPyr ? bPyr - aPyr : aPyr - bPyr) % 3;

    u8 aSqrMod3 = aSqr % 3;
    u8 bSqrMod3 = bSqr % 3;

    u8 modPyr = (bSqrMod3 > aSqrMod3 ? bSqrMod3 - aSqrMod3 : aSqrMod3 - bSqrMod3) % 3;

    u64 circleApprox = (current * 22 + 14) / 28;
    u8 csMod6 = (bSqrNoM - circleApprox) % 6;

    s8 grammarSeed = (aSqrNoM - bSqrNoM) % 100;
    
    new.cMod10 = aSqr + bSqr;
    new.pyramid = pyr;
    new.modPyramid = modPyr;
    new.csMod6 = csMod6;
    new.comp = aSqr + bSqr + pyr + modPyr + csMod6;
    new.grammarSeed = grammarSeed;

    return new;
}
    

void emitCandidateCSVHeader(FILE* out) {
    fprintf(out, "previous,current,is_prime,cMod10,pyramid,modPyramid,csMod6,grammarSeed,comp\n");
}

void emitCandidateCSVRow(FILE* out, u64 previous, u64 current, u8 isPrime, Candidate c) {
    fprintf(out, "%llu,%llu,%d,%u,%u,%u,%u,%d,%u\n",
        previous, current, isPrime,
        c.cMod10, c.pyramid, c.modPyramid, c.csMod6,
        c.grammarSeed, c.comp
    );
}


