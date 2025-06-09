#include "prime_triangle_filter.h"

// Internal helper for matching 1/9 pairs
static int is_good_mod10_pair(uint8_t a, uint8_t b) {
    return (a == 1 && b == 9) || (a == 9 && b == 1);
}

PrimeHeuristicResult triangle_heuristic(uint8_t a2_mod10, uint8_t b2_mod10, uint32_t gap) {
    // Disqualify immediately if either mod is 2 or 8 and the gap is very small
    if ((a2_mod10 == 2 || a2_mod10 == 8 || b2_mod10 == 2 || b2_mod10 == 8)) {
        if (gap <= 10) {
            return PRIME_DISQUALIFIED; // No twins form in this case
        }
        // If not close, allow it weakly
        return PRIME_MAYBE;
    }

    // 0s can form tight clusters (e.g., 3+7 = 10²), but they’re not twin-prone
    if ((a2_mod10 == 0 || b2_mod10 == 0)) {
        if (gap <= 6) {
            return PRIME_MAYBE;
        }
        return PRIME_DISQUALIFIED;
    }

    // Strong heuristic pattern: one ends in 1 and the other ends in 9
    if (is_good_mod10_pair(a2_mod10, b2_mod10)) {
        if (gap == 2) return PRIME_LIKELY; // Probable twin
        if (gap <= 6) return PRIME_MAYBE;
        return PRIME_LIKELY;
    }

    // All other combinations: no strong signal
    return PRIME_MAYBE;
}

//courtesy of jipppity... not good
