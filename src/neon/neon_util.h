#ifndef neon_NEON_UTIL_H
#define neon_NEON_UTIL_H

#include "common_types.h"

void initNEON_Array_u16(u16* src, u16 value, u64 size);
void copyNEON_Array_u16(u16* dst, u16* src, u64 size);
void initNEON_Array_u32(u32* src, u32 value, u64 size); 
void copyNEON_Array_u32(u32* dst, u32* src, u64 size); 

#endif
