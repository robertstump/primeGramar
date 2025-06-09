#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void generate_primes(uint64_t max) {
    if (max < 2) return;

    bool *is_prime = calloc(max + 1, sizeof(bool));
    if (!is_prime) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (uint64_t i = 2; i <= max; ++i) {
        is_prime[i] = true;
    }

    for (uint64_t i = 2; i * i <= max; ++i) {
        if (is_prime[i]) {
            for (uint64_t j = i * i; j <= max; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (uint64_t i = 2; i <= max; ++i) {
        if (is_prime[i]) {
            printf("%llu\n", (unsigned long long)i);
        }
    }

    free(is_prime);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <max>\n", argv[0]);
        return 1;
    }

    uint64_t max = strtoull(argv[1], NULL, 10);
    generate_primes(max);

    return 0;
}


//boilerplate prime generation curtesy of jippity.
//
//gcc generate_primes.c -generate_primes 
// ./generate_primes 100000 > primes.txt
//
// fast enough for millions etc
