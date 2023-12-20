#include "rsaf.h"

/**
 * infiX_mul - multiplies numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on malloc fail or if both strings are empty
 */
char *infiX_mul(char *n1, char *n2)
{
	ssize_t top, botm, c_dgt;
	int byt_mul = 0;
	char *prod = NULL, *c_mul = NULL, *total = NULL;

	for (botm = (ssize_t)_strlen(n2) - 1; botm >= 0; botm--)
	{
		c_dgt = (ssize_t)_strlen(n1) + ((ssize_t)_strlen(n2) - botm);
		c_mul = malloc(sizeof(*c_mul) * (c_dgt + 1));
		if (!c_mul)
			return (NULL);

		c_mul = memset(c_mul, '0', c_dgt);
		c_mul[c_dgt] = '\0';
		for (top = (ssize_t)_strlen(n1) - 1; top >= 0; top--)
		{
			byt_mul += ((n1[top] - '0') * (n2[botm] - '0'));
			c_mul[top + 1] = (byt_mul % 10) + '0';
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

	return (prod);
}
