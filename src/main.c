#include "Gsub210.h"
#include "geometerPattern.h"

u64 current;
u64 previous;
FILE* out;

u8 isPrime(u64 n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (u64 i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}
void outputCSVPrimeCandidate(u64 n) {
    u64 temp = (u64)n;
    if (!previous) {
        previous = temp;
        return;
    }

    current = temp;

    u8 primality = isPrime(current);
    Candidate new = getCandidate(previous, current);
    emitCandidateCSVRow(out, previous, current, primality, new);
    
    if(primality) {
        previous = current;
    }
}

//for Erasthones sieve use "void funcName(u32 n)
void outputCSVCandidate(u64 n) {
    u64 temp = (u64)n;
    if (!previous) {
        previous = temp;
        return;
    }

    current = temp;

    u8 primality = isPrime(current);
    Candidate new = getCandidate(previous, current);
    emitCandidateCSVRow(out, previous, current, primality, new);

    previous = current;
}

s32 main(void) {
    out = fopen("./prime_onlySieveLiveNegSeedMod.csv", "w");
    emitCandidateCSVHeader(out); 
    printf("START sieve....\n");
    naiveGsub210Scan(100000, outputCSVPrimeCandidate); 

    //initGsub210(); //need for Erasthones sieve, remove for niave Gsub210
    //sieveGsub210(2000, printCandidate); 

    fclose(out);
    return 0;
}

