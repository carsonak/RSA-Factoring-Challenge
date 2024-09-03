#!/usr/bin/env python3
"""Sieve of Atkin."""
# https://en.wikipedia.org/wiki/Sieve_of_Atkin
# https://www.geeksforgeeks.org/sieve-of-atkin/

# import line_profiler
import math
import numpy as np
from typing import Literal


def _get_numpy_type(n: int) -> type[np.unsignedinteger]:
    """Returns the smallest numpy data type that can hold n.

    Args:
        n: an integer.

    Returns:
        An instance of numpy.dtype.

    Raises:
        ValueError if n is greater than 2^128 - 1.
    """
    if n >= 2**128:
        raise ValueError(f"value out of range: {n:40}"
                         f"{"..." if n >= 10**40 else ""}")

    if n < 2**8:
        return np.uint8

    if n < 2**16:
        return np.uint16

    if n < 2**32:
        return np.uint32

    if n < 2**64:
        return np.uint64

    return np.uint128


def _sieve_to_ndarray(s: np.ndarray[Literal[1], bool]
                      ) -> np.ndarray[Literal[1], np.unsignedinteger]:
    """Converts a sieve of primes to a numpy array."""
    primes_count: int = 0
    largest_prime = 0
    for n, is_prime in enumerate(s):
        if is_prime:
            largest_prime = n
            primes_count += 1

    primes = np.empty(primes_count, dtype=_get_numpy_type(largest_prime))
    primes_count = 0
    for n, is_prime in enumerate(s):
        if is_prime:
            primes[primes_count] = n
            primes_count += 1

    return primes


# @line_profiler.profile
def sieve_of_atkin(limit: int) -> np.ndarray[Literal[1], np.unsignedinteger]:
    """Returns a list of primes from 0 to limit (inclusive).

    Args:
        limit: upper range of primes to find.

    Returns:
        A list of primes from 0 to limit.

    Raises:
        TypeError: if limit is not an int.
        ValueError: if limit does not satisfy: 0 <= limit < 2**64.
    """
    if type(limit) is not int:
        raise TypeError("limit should be an int type")

    if limit < 0:
        raise ValueError("limit cannot be a negative integer")

    if limit >= 2**64:
        raise ValueError("limit is greater than 2^64")

    sieve = np.zeros(limit + 1, dtype=bool)
    limit_sqrt = int(math.ceil(math.sqrt(limit)))
    x = 1
    while x <= limit_sqrt:
        y = 1
        x_sqr = x**2
        while y <= limit_sqrt:
            y_sqr = y**2
            n = (4 * x_sqr) + y_sqr
            # (n % 60 == {1,13,17,29,37,41,49,53}) same as (n % 12 == {1,5})
            if n <= limit and (n % 12 == 1 or n % 12 == 5):
                sieve[n] = not sieve[n]

            n = (3 * x_sqr) + y_sqr
            # (n % 60 == {7,19,31,43}) same as (n % 12 == {7})
            if n <= limit and n % 12 == 7:
                sieve[n] = not sieve[n]

            n = (3 * x_sqr) - y_sqr
            # (n % 60 == {11,23,47,59}) same as (n % 12 == {11})
            if n <= limit and x > y and n % 12 == 11:
                sieve[n] = not sieve[n]

            y += 1

        x += 1

    r = 5
    while r <= limit_sqrt:
        if sieve[r]:
            # If r is prime, mark all multiples of its square false.
            for i in range(r**2, limit + 1, r**2):
                sieve[i] = False

        r += 1

    if limit > 2:
        sieve[2] = True

    if limit > 3:
        sieve[3] = True

    return _sieve_to_ndarray(sieve)


if __name__ == "__main__":
    import sys
    n = 2 ** 16
    p = sieve_of_atkin(n)
    print(f"Primes in {n}: {len(p)}")
    print(f"Size of Array: {sys.getsizeof(p)}")
