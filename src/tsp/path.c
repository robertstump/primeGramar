#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

#include "common_types.h"
#include "neon_util.h"
#include "arena_base.h"
#include "page_arena.h"

//rob - these are dumb. don't do this once you can receive real values.
#define SIZE_OF_N size * sizeof(u16) 
#define SIZE_OF_ARENA MiB(10)

void update(u16* bit, u32 index, u32 delta, u32 size) {
    while (index <= size) {
        bit[index] += delta;
        index += index & -index;
    }
    return;
}

u32 prefix_sum(u16* bit, u32 index) {
    u32 sum = 0;
    while (index > 0) {
        sum += bit[index];
        index -= index & -index;
    }
    return sum;
}

u32 highestPow2(u32 size) {
    u32 pow = 1;
    u32 check;
    check = size >> 1;
    while (pow <= check) {
        pow <<= 1;
    }
    return pow;
}

u32 select_kth(u16* bit, u32 k, u32 size) {
    u32 position = 0;
    u32 mask = highestPow2(size);

    while (mask > 0) {
        u32 next = position + mask;
        if (next <= size && bit[next] <= k) {
            k -= bit[next];
            position = next;
        }
        mask >>= 1;
    }
    return position + 1;
}

void buildFenwick(u16* bit, u32 size) {
    for (u32 i = 1; i <= size; i++) {
        update(bit, i, 1, size);
    }
}

void decodeLehmerToPerm(u16 *bit, u32* lehmer, u32* perm, u32 size) {
    perm[0] = 0;

    for (u32 i = 0; i < size - 1; i++) {
        u32 k;
        k = lehmer[i];
        u32 city = select_kth(bit, k, size);
        perm[i + 1] = city;
        update(bit, city, -1, size);
    }
    return;
}

u64 factorial(u32 size) {
    u64 result = 1;
    for (u32 i = 2; i <= size; i++) {
        result *= i;
    }
    return result;
}

void generateLehmerCode(u32* lehmer, u32 size, u32 k) {
    for (u32 i = 0; i < size - 1; i++) {
        u32 base = size - 1 - i;
        u64 f = factorial(base - 1);
        lehmer[i] = (int)(k / f);
        k = k % f;
    }
}

void generateLehmerCode_stack(u32* lehmer, u32 index, u32 size, u32 sampleSize) {
    f64 ratio = ((f64)index + 0.5) / (f64)sampleSize;
    for (u32 j = 0; j < size - 1; j++) {
        u32 radix = size - 1 - j;
        ratio *= radix;
        lehmer[j] = (u32)ratio;
        ratio -= lehmer[j];
    }
}

void generateLehmerCode_shifted(u32* lehmer, u32 index, u32 size, u32 sampleSize) {
    f64 ratio = ((f64)index + 0.5) / (f64)sampleSize;

    const f64 min_entropy = DBL_EPSILON * 10;
    const u32 radix_floor = 2;

    for (u32 j = 0; j < size - 1; j++) {
        u32 radix = size - 1 - j;
        if(radix < radix_floor) radix = radix_floor;

        if (radix < radix_floor) radix = radix_floor;
        if (ratio < min_entropy) ratio *= radix;

        ratio *= radix;
        u32 digit = (u32)ratio;
        if (digit > radix) digit = radix;

        lehmer[j] = digit;
        ratio -= digit;
    }
}

int main() {
    u32 size = 200;
    memMap* map = initMemMap(SIZE_OF_ARENA * 4);
    PageArena* arena = createPageArena(map, MiB(5));
    u16 *bit = arenaPageAlloc(arena, (size + 2) * sizeof(u16), ALIGN_16);
    u16 *storedBit = arenaPageAlloc(arena, (size + 2) * sizeof(u16), ALIGN_16);
    u32 *lehmer = arenaPageAlloc(arena, sizeof(u32) * size, ALIGN_16);
    u32 *perm = arenaPageAlloc(arena, sizeof(u32) * size, ALIGN_16);
    u32 sampleSize = 2;

    buildFenwick(bit, size);
    for(u32 index = 0; index <= sampleSize; index++) {
        copyNEON_Array_u16(storedBit, bit, (u64)size + 2);

        generateLehmerCode_shifted(lehmer, index, size - 1, sampleSize);
        //generateLehmerCode_stack(lehmer, index, size - 1, sampleSize);   
        //generateLehmerCode(lehmer, size, index + 6);

        fprintf(stdout, "Lehmer: [");
        for(u16 i = 0; i < size; i++) {
            fprintf(stdout, "%u, ", lehmer[i]);
        }
        fprintf(stdout, "]\n");

        decodeLehmerToPerm(bit, lehmer, perm, size);

        copyNEON_Array_u16(bit, storedBit, (u64)size + 2);

        fprintf(stdout, "Permutation: [");
        for(u16 i = 0; i < size; i++) {
            fprintf(stdout, "%u, ", perm[i]);
        }
        fprintf(stdout, "]\n");
    }

    exit(0);
}

