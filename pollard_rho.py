#!/usr/bin/env python3
"""Calculate factors of composite numbers using Pollard's Rho algorithm."""
# https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

import math
import random


# https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/pollardsRho.html
def pollard_rho(num: int) -> int:
    """Returns prime divisor for a composite number."""
    if (num == 1 or num == 3):
        return 1

    # even number means one of the divisors is 2
    if (num % 2 == 0):
        return 2

    # 2 <= slow < num
    slow = random.randint(2, num - 1)
    fast = slow
    # The constant in f(x). 1 <= c < num-2
    c = random.randint(1, num - 3)
    factor = 1

    def randish(x: int) -> int:
        """Pseudo-random number generator."""
        return (x**2 + c) % num

    while (factor == 1):
        # Tortoise Move: x(i+1) = f(x(i))
        slow = randish(slow)
        # Hare Move: y(i+1) = f(f(y(i)))
        fast = randish(randish(fast))

        factor = math.gcd(abs(slow - fast), num)
        # Retry if the algorithm fails to find prime factor
        # with chosen slow and c
        if (factor == num):
            return pollard_rho(num)

    return factor


def pollard_brent_rho(num: int) -> int:
    """Returns prime divisor of a composite number."""
    if (num == 1):
        return num

    if (num % 2 == 0):
        return 2

    fast = random.randrange(1, num)
    c = random.randrange(1, num)
    m = random.randrange(1, num)
    factor, r, cumulative_mods = 1, 1, 1
    while factor == 1:
        slow, k = fast, 0
        for _ in range(r):
            fast = (fast**2 + c) % num

        while k < r and factor == 1:
            ys = fast
            for _ in range(min(m, r-k)):
                fast = (fast**2 + c) % num
                cumulative_mods *= abs(slow-fast) % num

            factor = math.gcd(cumulative_mods, num)
            k += m

        r *= 2

    if factor == num:
        while True:
            ys = (ys**2 + c) % num
            factor = math.gcd(abs(slow-ys), num)
            if factor > 1:
                break

    return factor
