#include "rsaf.h"

/**
 * sieve_o_atkins - generates a sieve to find prime numbers in a range
 * @range: the range
 *
 * Description: Uses a bit masking to reduce memory usage.
 *
 * Return: a pointer to the sieve, NULL on failure
 */
u_int8_t *sieve_o_atkins(u_int64_t range)
{
	int64_t limit = range, ulimit = 0;
	int64_t i, j, x, y, z;
	u_int8_t *sieb = NULL;

	sieb = calloc(((range / 8) + 1), sizeof(*sieb));
	if (!sieb)
	{
		perror("Block alocation failed\n");
		return (NULL);
	}

	ulimit = sqrt(limit);
	for (x = 1; x <= ulimit; x++)
	{
		for (y = 1; y <= ulimit; y++)
		{
			z = (4 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
				 z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) - (y * y);
			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}
		}
	}

	for (i = 5; i <= ulimit; i++)
		if (sieb[i / 8] & (1 << (i % 8)))
			for (j = 1; (j * i * i) <= limit; j++)
				sieb[(j * i * i) / 8] &= ~(1 << ((j * i * i) % 8));

	sieb[2 / 8] |= (1 << (2 % 8));
	sieb[3 / 8] |= (1 << (3 % 8));
	sieb[5 / 8] |= (1 << (5 % 8));
	return (sieb);
}
