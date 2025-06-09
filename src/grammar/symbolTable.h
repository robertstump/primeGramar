#ifndef g_SYMBOL_TABLE_H
#define g_SYMBOL_TABLE_H

#include "common_types.h"
#include "alpha2.h"

typedef struct {
    AtomicSymbol* entries;
    u32 capacity;
    u32 count;
} SymbolTable;

SymbolTable* initSymbolTable(SymbolTable* table);
AtomicSymbol* insertSymbol(SymbolTable* table, char symbol, u32 value);
AtomicSymbol* findSymbolByValue(SymbolTable* table, u32 value);
AtomicSymbol* findSymbolBySymbol(SymbolTable* table, char symbol);
u8 hasValue(SymbolTable* table, u32 value);
u8 hasSymbol(SymbolTable* table, char symbol);
void printSymbolTable(SymbolTable* table);

#endif
