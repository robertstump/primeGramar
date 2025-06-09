#include <stdlib.h>
#include "Gsub210.h"

u8 residue_lookup[210] = {0};

//use this version for Erasthones style sieve, use const for niave sieve.
//u32 Gsub210Residues[48];

static const u32 Gsub210Residues[48] = {
    1, 11, 13, 17, 19, 23, 29, 31,
    37, 41, 43, 47, 53, 59, 61, 67,
    71, 73, 79, 83, 89, 97, 101, 103,
    107, 109, 113, 121, 127, 131, 137, 139,
    143, 149, 151, 157, 163, 167, 169, 173,
    179, 181, 187, 191, 193, 197, 199, 209
};

void naiveGsub210Scan(u64 limit, void (*callback)(u64)) {
    for (u64 k = 0;; k++) {
        for (u64 i = 0; i < 48; i++) {
            u64 n = k * 210 + Gsub210Residues[i];
            if (n > limit) return;
            callback(n);
        }
    }
}
/*
u8 isGsub210(u32 n) {
    return residue_lookup[n % 210];
}

void initGsub210() {
    generateGCDResidues210(Gsub210Residues);
    for (u32 i = 0; i < 48; i++) {
    }
}

u32 gcd(u32 a, u32 b) {
    while (b != 0) {
        u32 temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generateGCDResidues210(u32* residues_out) {
    u32 count = 0;
    for(u32 i = 0; i < 210; i++) {
        if(gcd(i, 210) == 1) { 
            residue_lookup[i] = 1;
            if (residues_out) {
                residues_out[count++] = i;
            }
        }
    }
}

void generateGsub210Candidates(u32 limit, void (*callback)(u32)) {
    for(u32 k = 0;; k++) {
        for (u32 i = 0; i < 48; i++) {
            u32 n = k * 210 + Gsub210Residues[i];
            if (n > limit) return;
            callback(n);
        }
    }
}

u32 getCandidateIndex(u32 n, u32* residues) {
    u32 k = n / 210;
    u32 r = n % 210;

    for (u32 i = 0; i < 48; i++) {
        if (residues[i] == r) {
            return k * 48 + i;
        }
    }
    LOG_ERROR("r = %u not in residue list\n", r);
    assert(0);
}

u32 computeCandidateCount(u32 limit, u32* residues) {
    u32 count = 0;
    for (u32 k = 0;; k++) {
        for (u32 i = 0; i < 48; i++) {
            u32 n = k * 210 + residues[i];
            if (n > limit) {
                return count;
            }
            count++;
        }
    }
}

void sieveGsub210(u32 limit, void (*callback)(u32)) {
    printf("SIEVE PROCESSING....\n");
    u32 basePrimes[] = {1, 3, 5, 7};
    for (u32 i = 0; i < 4; i++) {
        if (basePrimes[i] <= limit) {
            callback(basePrimes[i]);
        }
    }
    u32 totalBits = computeCandidateCount(limit, Gsub210Residues);
    u8* bitArray = calloc((totalBits + 7) / 8, 1);

    for (u32 pk = 0;; pk++) {
        for (u32 pi = 0; pi < 48; pi++) {
            u32 p = pk * 210 + Gsub210Residues[pi];
            if (p == 1) continue;
            if (p * p > limit) goto mark_done;

            u32 p_index = pk * 48 + pi;
            if (bitArray[p_index / 8] & (1 << (p_index % 8))) {
                continue;
            }

            for (u32 qk = pk;; qk++) {
                for (u32 qi = (qk == pk) ? pi : 0; qi < 48; qi++) {
                    u32 q = qk * 210 + Gsub210Residues[qi];
                    u64 n = (u64)p * q;
                    if (n > limit) goto next_p;

                    u32 n_index = getCandidateIndex((u32)n, Gsub210Residues);
                    bitArray[n_index / 8] |= (1 << (n_index % 8));
                }
            }
        next_p: ;
        }
    }

mark_done:
    for (u32 k = 0, idx = 0;; k++) {
        for (u32 i = 0; i < 48; i++, idx++) {
            u32 n = k * 210 + Gsub210Residues[i];
            if (n > limit) goto done;

            if ((bitArray[idx / 8] & (1 << (idx % 8))) == 0) {
                callback(n);
            }
        }
    }
done:
    free(bitArray);
}
*/
