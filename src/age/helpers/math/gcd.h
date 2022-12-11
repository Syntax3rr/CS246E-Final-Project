#ifndef AGE_HELPERS_MATH_GCD_H_
#define AGE_HELPERS_MATH_GCD_H_
#include <cmath>

// Returns the greatest common divisor of integers a and b.

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    // Euclid's algorithm
    if (a == 0) return b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

#endif
