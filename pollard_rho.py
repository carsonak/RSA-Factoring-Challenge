#!/usr/bin/env python3
"""Calculate factors of composite numbers using Pollard's Rho algorithm."""
# https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
# https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/pollardsRho.html
# https://en.algorithmica.org/hpc/algorithms/factorization/

import math
import random


class Randish:
    """Pseudo-random number genarator."""

    def __init__(self, seed: int) -> None:
        """Initialises the constant."""
        self.c = seed

    def gen(self, x: int, ub: int) -> int:
        """Generates a pseudo-random positive integer.

        Args:
            x: value to be used in the polynomial.
            ub: upper bound of the numbers to generate.

        Return:
            An int less than ub.
        """
        return (x**2 + self.c) % ub


def pollard_rho(num: int) -> int:
    """Calculates prime divisor for a composite number.

    Args:
        num: a composite number.

    Return:
        Smallest prime factor of num.
    """
    # even number means one of the divisors is 2
    if (num % 2 == 0):
        return 2

    # 2 <= slow < num
    slow = random.randint(2, num - 1)
    fast = slow
    # Pseudo-random number generator.
    rand = Randish(random.randint(1, num - 2))
    factor = 1
    while (factor == 1):
        # Tortoise Move: x(i+1) = f(x(i))
        slow = rand.gen(slow, num)
        # Hare Move: y(i+1) = f(f(y(i)))
        fast = rand.gen(rand.gen(fast, num), num)

        factor = math.gcd(abs(slow - fast), num)
        # Retry if the algorithm fails to find prime factor
        # with chosen slow and c
        if (factor == num):
            return pollard_rho(num)

    return factor


def pollard_brent_rho(num: int) -> int:
    """Calculates prime divisor for a composite number.

    Args:
        num: a composite number.

    Return:
        Smallest prime factor of num.
    """
    # Pseudo-random number generator.
    rand = Randish(random.randint(1, num - 2))
    m = 13
    fast = random.randint(2, num - 1)
    cumulative_diff, factor, r = 1, 1, 1
    while factor == 1:
        slow = fast
        for _ in range(r):
            fast = rand.gen(fast, num)

        k = 0
        while k < r and factor == 1:
            fast2 = fast
            for _ in range(min(m, r-k)):
                fast = rand.gen(fast, num)
                cumulative_diff *= abs(slow - fast) % num

            factor = math.gcd(cumulative_diff, num)
            k += m

        r *= 2

    if factor == num:
        fast2 = rand.gen(fast2, num)
        factor = math.gcd(abs(slow - fast2), num)
        while factor == 1:
            fast2 = rand.gen(fast2, num)
            factor = math.gcd(abs(slow - fast2), num)

    return factor
