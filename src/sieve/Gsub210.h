#ifndef SIEVE_GSUB210_H
#define SIEVE_GSUB210_H

#include "common_types.h"

//use with Erasthones sieve
//extern u32 Gsub210Residues[48];

u8 isGsub210(u32 n);
void initGsub210();
u32 gcd(u32 a, u32 b);
void generateGCDResidues210(u32* residues_out); 
void generateGsub210Candidates(u32 limit, void (*callback)(u32));
u32 getCandidateIndex(u32 n, u32* residues);
u32 computeCandidateCount(u32 limit, u32* residues);
void sieveGsub210(u32 limit, void (*callback)(u32));
void naiveGsub210Scan(u64 limit, void (*callback)(u64));

#endif

