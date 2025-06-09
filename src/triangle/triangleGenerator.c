#include "common_types.h"
#include "arena_base.h"
#include "page_arena.h"
#include "triangleGenerator.h"

void getA(tPoint* A, u32 size) {
    if (size < 1) {
        LOG_ERROR("Generation must not go under 1");
    }
    u32 step = size - 1;
    u8 direction = step % 4;
    s8 direction_x = 0;
    s8 direction_y = 0;

    switch (direction) {
        case 0:
            direction_y = -1;
            break;
        case 1:
            direction_x = 1;
            break;
        case 2:
            direction_y = 1;
            break;
        case 3:
            direction_x = -1;
            break;
        default:
            break;
    }
    u32 ring = (u32)(step / 4 + 1);
    A->direction = direction;
    A->x = direction_x * ring;
    A->y = direction_y * ring;
}

void getB(tPoint* A, tPoint* B, u32 size) {
    switch (A->direction) {
        case 0:
            B->x = A->x * size;
            B->y = A->y * size;
            break;
        case 1: 
            B->x = A->x * size;
            B->y = A->y * size;
            break;
        case 2:
            B->x = A->x * size;
            B->y = A->y * size;
            break;
        case 3:
            B->x = A->x * size;
            B->y = A->y * size;
            break;
        default: 
            break;
    }
}

u8 isGsub6(u32 n) {
    return n > 3 && (n % 6 == 1 || n % 6 == 5) && n % 5 != 0;
}

