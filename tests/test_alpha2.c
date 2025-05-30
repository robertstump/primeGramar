#include "minunit.h"
#include "dbg.h"
#include "arena_base.h"
#include "page_arena.h"
#include "common_types.h"
#include "alpha2.h"

#define MAP_SIZE GiB(1)

mu_suite_start();
s32 tests_run = 0;

char* test_make_nodes() {
    memMap *map = initMemMap(MAP_SIZE);
    PageArena *nodeArena = createPageArena(map, KiB(4));
    PageArena *dataArena = createPageArena(map, KiB(4)); 
    
    AtomicSymbol zero   = { .symbol = '0', .value = 0 };
    AtomicSymbol one    = { .symbol = 'a', .value = 1 };
    AtomicSymbol three  = { .symbol = 'b', .value = 3 };
    AtomicSymbol five   = { .symbol = 'c', .value = 5 };

    AtomicSymbol dataA[3] = {one, one, zero};
    AtomicSymbol dataB[3] = {one, one, zero};
    AtomicSymbol dataC[3] = {one, three, five};
    GrammarNode *a = createGrammarNode(nodeArena, dataArena, 2, dataA, 3);
    GrammarNode *b = createGrammarNode(nodeArena, dataArena, 2, dataB, 3);
    GrammarNode *c = createGrammarNode(nodeArena, dataArena, 2, dataC, 3);
    mu_assert(compareAlpha(a, b, a->size) == TRUE, "Like nodes should compare true\n");
    mu_assert(compareAlpha(a, c, a->size) == FALSE, "Unlike nodes should compare false\n");
    mu_assert(isAlphaValid(c) == FALSE, "Key values should not mismatch\n");

    AtomicSymbol dataD[3] = { three, three, three };
    GrammarNode *d = createGrammarNode(nodeArena, dataArena, 9, dataD, 3);
    GrammarNode *e = createGrammarNode(nodeArena, dataArena, 9, dataD, 3);
    GrammarNode* result = insertIfUnique(e, d);
    mu_assert(result->next == e, "Insert failed two keyed values\n");
    mu_assert(result == d, "Insert result incorrect\n");
    mu_assert(result != NULL, "Insert result should not be NULL\n");

    mu_assert(insertIfUnique(d, a) == NULL, "Should not insert on wrong value");

    arenaPagePop(map);
    arenaPagePop(map);
    releasePages(map);
    PASS_TEST("Alpha create and compare success");
    return NULL;
}

static char* all_tests() {
    mu_run_test(test_make_nodes);
    return NULL;
}

RUN_TESTS(all_tests);

