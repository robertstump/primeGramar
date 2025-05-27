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

GrammarNode* insertIfUnique(GrammarNode** head, GrammarNode* newNode) {
    if (*head == NULL) {
        *head = newNode;
        newNode->next = NULL;
        return newNode;
    }

    GrammarNode* current = *head;
    GrammarNode* prev = NULL;
    while (current != NULL) {
        if (compareAlpha(current, newNode, newNode->size) == TRUE) {
            return current;
        }
        prev = current;
        current = current->next;
    }

    prev->next = newNode;
    newNode->next = NULL;
    return newNode;
}

void printGrammarFor(u32 value, GrammarNode* head) {
    fprintf(stdout, "Key: %u - ", value);
    GrammarNode* current = head;
    while (current->next != NULL) {
        u16* cptr = (u16*)current->alpha;
        fprintf(stdout, "Alpha%u: ", current->key);
        for (u32 i = 0; i < current->size; i++) {
            fprintf(stdout, "%u ", cptr[i]);
        }
        fprintf(stdout, " | ");
        current = current->next;
    }       
    fprintf(stdout, "\n");
}

