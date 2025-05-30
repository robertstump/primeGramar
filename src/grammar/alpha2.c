#include "alpha2.h"

enum boolCode compareAlpha(GrammarNode* a, GrammarNode* b, u16 size) {
    require(a->size == size && b->size == size, "Invalid comparison between mismatched sizes\n"); 

    for (u32 i = 0; i < size; i++) {
        if(a->alpha[i].symbol != b->alpha[i].symbol) {
            return FALSE;
        }
    }
    return TRUE;
}

enum boolCode isAlphaValid(GrammarNode* a) {
    u32 result = 0;

    for(u32 i = 0; i < a->size; i++) {
        result += a->alpha[i].value;
    }
    if (result != a->key ) {
        LOG_INFO("Composite sum %u does not equal key %u\n", result, a->key);
        return FALSE;
    }
    return TRUE;
}

GrammarNode* createGrammarNode(PageArena* nodeArena, PageArena* alphaArena, u32 key, AtomicSymbol* values, u16 size) {
    GrammarNode* node = arenaPageAlloc(nodeArena, sizeof(GrammarNode), ALIGN_4);
    if(!node) return NULL;

    AtomicSymbol* data = arenaPageAlloc(alphaArena, sizeof(AtomicSymbol) * size, ALIGN_2);
    if(!data) return NULL;

    for (u16 i = 0; i < size; i++) {
        data[i] = values[i];
    }

    node->key = key;
    node->size = size;
    node->alpha = data;
    node->next = NULL;

    return node;
}

GrammarNode* insertIfUnique(GrammarNode* head, GrammarNode* newNode) {
    if (head == NULL) {
        return NULL;
    }

    GrammarNode* current = head;
    if (current->key != newNode->key) {
        LOG_INFO("Key not same between insertion values");
        return NULL;
    }

    if (compareAlpha(current, newNode, newNode->size) == TRUE) {
        return NULL;
    }

    newNode->next = head;
    return newNode;
}

void printGrammarChain(u32 key, GrammarNode* head) {
    printf("=== Grammar Expansions for Key %u ===\n", key);

    if(!head) {
        printf(" <none>\n");
        return;
    }

    u32 count = 0;
    for (GrammarNode* node = head; node != NULL; node = node->next) {
        printf(" Alpha[%u]: ", node->size);
        for (u16 i = 0; i < node->size; i++) {
            printf("%u ", node->alpha[i].symbol);
        }
        printf("\n");
        count++;
    }

    printf(" [Total: %u expansions]\n", count);
    printf("-------------------------------------\n");
}


