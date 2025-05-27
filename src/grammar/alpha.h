#ifndef g_ALPHA_H
#define g_ALPHA_H

#include "common_types.h"

#define require(expr, msg) do { if (!(expr)) { LOG_ERROR(msg); return INVALID; } } while(0)

enum boolCode {
    FALSE = 0,
    TRUE = 1,
    INVALID = 2 
};

#define alpha1 u16

typedef struct {
    u16 a;
    u16 b;
} alpha2;

typedef struct {
    u16 a;
    u16 b;
    u16 c;
} alpha3;

typedef struct { 
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    u16 e;
} alpha4;

typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    u16 e;
    u16 f;
} alpha5;

typedef struct GrammarNode{
    u32 key;
    void* alpha;
    GrammarNode* next;
    u16 size;
} GrammarNode;

enum boolCode compareAlpha(const void* a, const void* b, u16 size);
u8 isAlphaValid(const GrammarNode* a);

/*
typedef struct {
    u32 key; //key by actual enumeration
    GrammarNode* value;
    u8 isOccupied;
} Entry;

typedef struct {
    Entry* entries;
    u32 capacity;
    u32 count;
} HashMap;

HashMap initHashMap(u32 size);
void insertHashMap(HashMap map, u16 key, Entry entry);
Entry getHashMap(HashMap map, u16 key);
HashMap resizeHashMap(HashMap map, u32 multiplier);
void destroyHashMap(HashMap map);
*/

#endif
