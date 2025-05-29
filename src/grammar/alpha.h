#ifndef g_ALPHA_H
#define g_ALPHA_H

#include "arena_base.h"
#include "page_arena.h"
#include "common_types.h"

#define require(expr, msg) do { if (!(expr)) { LOG_ERROR(msg); return INVALID; } } while(0)

enum boolCode {
    FALSE = 0,
    TRUE = 1,
    INVALID = 2 
};

typedef struct GrammarNode{
    u32 key;
    struct GrammarNode* next;
    u16* alpha;
    u16 size;
} GrammarNode;

enum boolCode compareAlpha(const GrammarNode* a, const GrammarNode* b, u16 size);
enum boolCode isAlphaValid(const GrammarNode* a);
GrammarNode* createGrammarNode(PageArena* nodeArena, PageArena* alphaArena, u32 key, u16* values, u16 size);
GrammarNode* insertIfUnique(GrammarNode* head, GrammarNode* newNode);

void printGrammarChain(u32 key, GrammarNode* head);


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
