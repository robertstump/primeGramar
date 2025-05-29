#include "minunit.h"
#include "dbg.h"
#include "arena_base.h"
#include "page_arena.h"
#include "common_types.h"
#include "alpha.h"

#define MAP_SIZE GiB(1)

mu_suite_start();
s32 tests_run = 0;

char* test_make_nodes() {
    memMap *map = initMemMap(MAP_SIZE);
    PageArena *nodeArena = createPageArena(map, (usize)sizeof(GrammarNode) * 5);
    PageArena *dataArena = createPageArena(map, (usize)sizeof(u16) * 5 * 3);

    u16 dataA[3] = {1, 2, 3};
    u16 dataB[3] = {1, 2, 3};
    u16 dataC[3] = {2, 3, 4};
    GrammarNode *a = createGrammarNode(nodeArena, dataArena, 6, (u16*)dataA, 3);
    GrammarNode *b = createGrammarNode(nodeArena, dataArena, 6, (u16*)dataB, 3);
    GrammarNode *c = createGrammarNode(nodeArena, dataArena, 6, (u16*)dataC, 3);
    mu_assert(compareAlpha(a, b, a->size) == TRUE, "Like nodes should compare true\n");
    mu_assert(compareAlpha(a, c, a->size) == FALSE, "Unlikes nodes should compare false\n");
    mu_assert(isAlphaValid(c) == FALSE, "Key values should not mismatch\n");

    u16 dataD[3] = {2, 2, 2};
    GrammarNode *d = createGrammarNode(nodeArena, dataArena, 6, (u16*)dataD, 3);
    GrammarNode* result = insertIfUnique(a, d);
    mu_assert(result->next == a, "Insert failed two keyed values\n");
    mu_assert(result == d, "Insert result incorrect\n");
    mu_assert(result != NULL, "Insert result should not be NULL\n");

    GrammarNode *e = createGrammarNode(nodeArena, dataArena, 9, (u16*)dataC, 3);
    mu_assert(insertIfUnique(d, e) == NULL, "Should not insert on wrong value");
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
