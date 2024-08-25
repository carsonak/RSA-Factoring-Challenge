#!/usr/bin/env python3
"""Sieve of Atkin."""
# https://en.wikipedia.org/wiki/Sieve_of_Atkin
# https://www.geeksforgeeks.org/sieve-of-atkin/

import numpy as np
from typing import List


def sieve_of_atkin(limit: int) -> List[int]:
    """Returns a list of primes from 0 to limit (inclusive).

    Args:
        limit: upper range of primes to find.

    Return:
        A list of primes from 0 to limit.
    """
    primes: List[int] = []
    if limit >= 2:
        primes.append(2)

    if limit >= 3:
        primes.append(3)

    sieve = np.zeros(limit + 1, np.bool)
    x = 1
    while x**2 <= limit:
        y = 1
        while y**2 <= limit:
            n = (4 * x**2) + y**2
            # (n % 60 == {1,13,17,29,37,41,49,53}) == (n % 12 == {1,5})
            if n <= limit and (n % 12 == 1 or n % 12 == 5):
                sieve[n] = not sieve[n]

            n = (3 * x**2) + y**2
            # (n % 60 == {7,19,31,43}) == (((n % 60) % 12) == n % 12 == {7})
            if n <= limit and n % 12 == 7:
                sieve[n] = not sieve[n]

            n = (3 * x**2) - y**2
            # (n % 60 == {11,23,47,59}) == (((n % 60) % 12) == n % 12 == {11})
            if n <= limit and x > y and n % 12 == 11:
                sieve[n] = not sieve[n]

            y += 1

        x += 1

    r = 5
    while r**2 <= limit:
        if sieve[r]:
            # If r is prime, mark all multiples of its square false.
            for i in range(r**2, limit + 1, r**2):
                sieve[i] = False

        r += 1

    primes += [x for x in range(5, limit + 1) if sieve[x]]
    return primes


if __name__ == "__main__":
    p = sieve_of_atkin(2 ** 32)
    print(f"\n{len(p)}")
