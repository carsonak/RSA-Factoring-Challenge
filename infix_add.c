#include "rsaf.h"

/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on malloc fail or if both strings are empty
 */
char *infiX_add(char *n1, char *n2)
{
	ssize_t a = 0, b = 0, byt_sum = 0, sum_i = 0;
	char *sum = NULL;

	n1 += n1 ? pad_char(n1, "0") : 0;
	n2 += n2 ? pad_char(n2, "0") : 0;
	a = n1 ? (ssize_t)(_strlen(n1) - 1) : -1;
	b = n2 ? (ssize_t)(_strlen(n2) - 1) : -1;
	sum_i = (a > b) ? a : b;
	if (sum_i < 0)
		return (NULL);

	sum = malloc(sizeof(*sum) * ((++sum_i) + 2));
	if (!sum)
		return (NULL);

	sum[sum_i + 1] = '\0';
	sum[0] = '0';
	while (a >= 0 || b >= 0 || byt_sum > 0)
	{
		if (a >= 0)
		{
			byt_sum += (n1[a] - '0');
			--a;
		}

		if (b >= 0)
		{
			byt_sum += (n2[b] - '0');
			--b;
		}

		sum[sum_i] = (byt_sum % 10) + '0';
		byt_sum /= 10;
		--sum_i;
	}

	return (sum);
}
