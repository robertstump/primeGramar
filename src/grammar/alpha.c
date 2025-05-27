#include "alpha.h"

enum boolCode compareAlpha(const GrammarNode* a, const GrammarNode* b, u16 size) {
    require(a->size == size && b->size == size, "Invalid comparison between mismatched sizes\n"); 

    u16* aptr = (u16*)a->alpha;
    u16* bptr = (u16*)b->alpha;

    for (u32 i = 0; i < size; i++) {
        if(aptr[i] != bptr[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

enum boolCode isAlphaValid(const GrammarNode* a) {
    u32 result = 0;

    u16* aptr = (u16*)a->alpha;

    for(u32 i = 0; i < a->size; i++) {
        result += aptr[i];
    }
    if (result != a->key) {
        LOG_ERROR("Composite sum %u does not equal key %u\n", result, a->key);
        return FALSE;
    }
    return TRUE;
}

GrammarNode* insertIfUnique(GrammarNode** head, GrammarNode* new) {
    return new;
}

