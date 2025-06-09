#ifndef BITMASK_SQUARE_FILTER_H
#define BITMASK_SQUARE_FILTER_H

#include <stdint.h>
#include <stdbool.h>

// Squares ending in 1 or 9 in base 10 end in specific 4-bit binary patterns.
// Base 10 values:
//   1  → 0001
//   9  → 1001 or 0111 (7^2 = 49, 3^2 = 9)

static inline bool ends_in_1_or_9(uint64_t x) {
    uint8_t last4 = x & 0b1111;  // Mask last 4 bits
    return (last4 == 0b0001 ||   // 1
            last4 == 0b0111 ||   // 7 (49)
            last4 == 0b1001);    // 9
}

// Optional: Only check for squares ending in 1
static inline bool ends_in_1(uint64_t x) {
    return (x & 0b1111) == 0b0001;
}

// Optional: Only check for squares ending in 9
static inline bool ends_in_9(uint64_t x) {
    uint8_t last4 = x & 0b1111;
    return (last4 == 0b1001 || last4 == 0b0111);
}

#endif // BITMASK_SQUARE_FILTER_H

//bitmask curtesy of jippity... junk. not even the right values... but it got the basics close.
