#ifndef g_ALPHA_TWO_H
#define g_ALPHA_TWO_H

#include "arena_base.h"
#include "page_arena.h"
#include "common_types.h"

#define require(expr, msg) do { if (!(expr)) { LOG_ERROR(msg); return INVALID; } } while(0)

enum boolCode {
    FALSE = 0,
    TRUE = 1,
    INVALID = 2 
};

typedef struct AtomicSymbol {
    char symbol;
    u32 value;
} AtomicSymbol;

typedef struct GrammarNode{
    AtomicSymbol* alpha;
    struct GrammarNode* next;
    u32 key;
    u16 size;
} GrammarNode;

enum boolCode compareAlpha(GrammarNode* a, GrammarNode* b, u16 size);
enum boolCode isAlphaValid(GrammarNode* a);
GrammarNode* createGrammarNode(PageArena* nodeArena, PageArena* alphaArena, u32 key, AtomicSymbol* values, u16 size);
GrammarNode* insertIfUnique(GrammarNode* head, GrammarNode* newNode);

void printGrammarChain(u32 key, GrammarNode* head);

#endif
