#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

// Check if number is in G6 (i.e., 6k ± 1)
bool is_G6(int n) {
    return n > 3 && (n % 6 == 1 || n % 6 == 5);
}

// Compute S(n): difference of max and min digits in base-6 * log2(n)
int S_atomic_diff(int n) {
    int max_digit = 0, min_digit = 5; // base-6 digits go from 0 to 5
    int temp = n;
    while (temp > 0) {
        int digit = temp % 6;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
        temp /= 6;
    }
    int depth = (int)(log2(n));
    return (max_digit - min_digit) * depth;
}

int hybrid_test(int n) {
    int s = S_atomic_diff(n);
    double angle =((double)s + s / (double)n);
    double cos_sq = cos(angle);
    return (int)round(cos_sq);
}

int main() {
    printf("n,S(n),HybridResult\n");
    for (int n = 5; n <= 500; ++n) {
        if (is_G6(n)) {
            int s = S_atomic_diff(n);
            int result = hybrid_test(n);
            printf("%d,\t%d,\t%d\n", n, s, result);
        }
    }
    return 0;
}

