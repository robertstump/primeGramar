#ifndef t_TRIANGLE_GEN_H
#define t_TRIANGLE_GEN_H

typedef struct {
    s32 x, y;
    s8 direction;
} tPoint;

typedef struct {
    tPoint A;
    tPoint B;
} Triangle;

void getA(tPoint* A, u32 size);
void getB(tPoint* A, tPoint* B, u32 size);
u8 isGsub6(u32 n);

#endif
