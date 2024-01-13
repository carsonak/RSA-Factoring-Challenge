#include "rsaf.h"

/**
 * sieve_o_atkins - generates a sieve to find prime numbers upto a given limit
 * @range: the range of numbers to sieve from 0
 *
 * Description: Uses a bit mask to mark prime numbers in the range
 *
 * Return: 1 on success, 0 on failure
 */
int sieve_o_atkins(int64_t limit)
{
	int64_t ulimit = sqrt(limit), x = 0, y = 0, z = 0, i = 0, j = 0;

	for (x = 1; x <= ulimit && !interrupted; x++)
	{
		for (y = 1; y <= ulimit && !interrupted; y++)
		{
			z = (4 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
				 z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
			{
				if (sieve[z / 8] & (1 << (z % 8)))
					sieve[z / 8] &= ~(1 << (z % 8));
				else
					sieve[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
			{
				if (sieve[z / 8] & (1 << (z % 8)))
					sieve[z / 8] &= ~(1 << (z % 8));
				else
					sieve[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) - (y * y);
			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
			{
				if (sieve[z / 8] & (1 << (z % 8)))
					sieve[z / 8] &= ~(1 << (z % 8));
				else
					sieve[z / 8] |= (1 << (z % 8));
			}
		}
	}

	sieve[2 / 8] |= (1 << (2 % 8));
	sieve[3 / 8] |= (1 << (3 % 8));
	sieve[5 / 8] |= (1 << (5 % 8));
	for (i = 5; i <= ulimit && !interrupted; i++)
		if (sieve[i / 8] & (1 << (i % 8)))
			for (j = 1; (j * i * i) <= limit && !interrupted; j++)
				sieve[(j * i * i) / 8] &= ~(1 << ((j * i * i) % 8));

	if (msync(sieve, SV_PG_MEM, MS_ASYNC | MS_INVALIDATE) == -1)
	{
		perror("Writing Failed");
		return (0);
	}

	return (1);
}
