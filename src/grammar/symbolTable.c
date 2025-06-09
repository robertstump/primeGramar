#include "symbolTable.h"
#include <string.h>
#include <stdio.h>

SymbolTable* initSymbolTable(PageArena* arena, u32 max) {
    SymbolTable* table;
    table->entries = arenaPageAlloc(arena, sizeof(AtomicSymbol) * max, ALIGN_4);
    table->capacity = max;
    table->count = 0;
    return table;
}

AtomicSymbol* insertSymbol(SymbolTable* table, char symbol, u32 value) {
    if(table->count >= table->capacity) {
        LOG_ERROR("Table already at capacity before insertion, returns NULL");
        return NULL;
    }
    if(hasValue(table, value) {
        LOG_WARN("Duplicate symbol detected: %c", symbol);
        return NULL;
    }
    AtomicSymbol* entry = &table->entries[table->count++];
    entry->symbol = symbol;
    entry->value = value;
    return entry;
}

AtomicSymbol* findSymbolByValue(SymbolTable* table, u32 value) {
    for (u32 i = 0; i < table->count; i++) {
        if (table->entries[i].value == value) return &table->entries[i];
    }
    LOG_INFO("Symbol not found for value: %u", value);
    return NULL;
}

AtomicSymbol* findSymbolBySymbol(SymbolTable* table, char symbol) {
    for (u32 i = 0; i < table->count; i++) {
        if(table->entries[i].symbol == symbol) return &table->entries[i];
    }
    LOG_INFO("Symbol not found for symbol: %c", symbol);
    return NULL;
}

u8 hasValue(SymbolTable* table, u32 value) {
    return findSymbolByValue(table, value) != NULL;
}

u8 hasSymbol(SymbolTable* table, char symbol) {
    return findSymbolBySymbol(table, symbol) != NULL;
}

void printSymbolTable(SymbolTable* table) {
    printf("=== Atomic Symbol Table ===\n");
    for(u32 i = 0; i < table->count; i++) {
        printf("%c => %u\n", table->entries[i].symbol, table->entries[i].value);
    }
    printf("[Total: %u entries]\n", table->count);
}
