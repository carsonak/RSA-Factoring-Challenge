#include "infix.h"

/**
 * infiX_mul - multiplies numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: string with the result, NULL on failure
 */
uint8_t *infiX_mul(uint8_t *n1, uint8_t *n2)
{
	ssize_t top = 0, botm = 0, c_dgt = 0, t = 0, b = 0;
	int byt_mul = 0;
	uint8_t *prod = NULL, *c_mul = NULL, *total = NULL;

	top = n1 ? (ssize_t)strlen((char *)n1) : 0;
	botm = n2 ? (ssize_t)strlen((char *)n2) : 0;
	if (top < 1 || botm < 1)
		return (NULL);

	for (b = botm - 1; b >= 0; b--)
	{
		if (n2[b] == '0')
			continue;

		c_dgt = top + (botm - b);
		c_mul = calloc((c_dgt + 2), sizeof(*c_mul));
		if (!c_mul)
		{
			perror("Malloc fail");
			return (NULL);
		}

		c_mul = memfill(c_mul, '0', (size_t)top, (size_t)(botm - b));
		c_mul[0] = '0';
		for (t = top - 1; t >= 0; t--)
		{
			byt_mul += ((n1[t] - '0') * (n2[b] - '0'));
			c_mul[t + 1] = (byt_mul % 10) + '0';
			byt_mul /= 10;
		}

		c_mul[0] = (byt_mul % 10) + '0';
		byt_mul = 0;
		prod = infiX_add(total, c_mul);
		free(c_mul);
		if (total)
			free(total);

		if (!prod)
			return (NULL);

		total = prod;
	}

	if (!prod)
	{
		prod = calloc(2, sizeof(*prod));
		if (!prod)
		{
			perror("Malloc fail");
			return (NULL);
		}

		prod[0] = '0';
	}

	return (prod);
}
