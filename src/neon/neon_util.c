#include <arm_neon.h>
#include "neon_util.h"

void initNEON_Array_u16(u16* dst, u16 value, u64 size) {
    n16x8 v = vdupq_n_u16(value);
    u64 i = 0;

    for(; i + 7 <= size; i += 8) {
        vst1q_u16(&dst[i], v);
    }

    for(; i < size + 1; ++i) {
        dst[i] = value;
    }
}
 
void copyNEON_Array_u16(u16* dst, u16* src, u64 size) {
    u64 i = 0;
    for(; i + 7 < size; i += 8) {
        n16x8 chunk = vld1q_u16(&src[i]);
        vst1q_u16(&dst[i], chunk);
    }
    for (; i < size; i++) {
        dst[i] = src[i];
    }
}

void initNEON_Array_u32(u32* dst, u32 value, u64 size) {
    n16x8 v = vdupq_n_u32(value);
    u64 i = 0;

    for(; i + 3 <= size; i += 4) {
        vst1q_u32(&dst[i], v);
    }

    for(; i < size + 1; ++i) {
        dst[i] = value;
    }
}
 
void copyNEON_Array_u32(u32* dst, u32* src, u64 size) {
    u64 i = 0;
    for(; i + 3 < size; i += 4) {
        n32x4 chunk = vld1q_u32(&src[i]);
        vst1q_u32(&dst[i], chunk);
    }
    for (; i < size; i++) {
        dst[i] = src[i];
    }
}

