#ifndef PRIME_TRIANGLE_FILTER_H
#define PRIME_TRIANGLE_FILTER_H

#include <stdint.h>

// Heuristic return values
typedef enum {
    PRIME_DISQUALIFIED = 0,
    PRIME_MAYBE = 1,
    PRIME_LIKELY = 2
} PrimeHeuristicResult;

/**
 * Evaluates the square mod-10 heuristic for a pair of primes.
 * 
 * This heuristic is based on detecting favorable mod 10 patterns (e.g., 1+9, 9+1),
 * and avoiding known low-value combinations (e.g., 2, 8).
 * 
 * Returns:
 *  - PRIME_DISQUALIFIED: known bad combination (e.g. 8s or 2s in twin-eligible range)
 *  - PRIME_MAYBE: rare pattern that doesn't disqualify but isn't strongly predictive
 *  - PRIME_LIKELY: favorable pair (1/9 pattern or known clustering pattern)
 */
PrimeHeuristicResult triangle_heuristic(uint8_t a2_mod10, uint8_t b2_mod10, uint32_t gap);

#endif // PRIME_TRIANGLE_FILTER_H


//courtesy of jippity. not good lol
