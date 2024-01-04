#include "infix.h"

/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on failure
 */
uint8_t *infiX_add(uint8_t *n1, uint8_t *n2)
{
	ssize_t a = 0, b = 0, byt_sum = 0, sum_i = 0;
	uint8_t *sum = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	b = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
	sum_i = (a > b) ? a : b;
	if (sum_i < 0)
		return (NULL);

	sum = calloc(((++sum_i) + 2), sizeof(*sum));
	if (!sum)
	{
		perror("Malloc fail");
		return (NULL);
	}

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
