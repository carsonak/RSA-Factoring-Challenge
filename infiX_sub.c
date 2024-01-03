#include "infix.h"

/**
 * infiX_sub - subtracts numbers in a string
 * @n1: number to be subtracted
 * @n2: number to subtract
 *
 * Return: a string of the result, NULL on failure
 */
uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2)
{
	ssize_t a = 0, b = 0, res_i = 0, diff = 0;
	int byt_res = 0;
	uint8_t *res = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	b = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
	res_i = (a > b) ? a : b;
	if (res_i < 0)
		return (NULL);

	if (a >= 0 && b >= 0 && a == b)
	{
		for (diff = 0; n1[diff] && n2[diff]; diff++)
		{
			if (n1[diff] == n2[diff])
				res_i--;
			else
				break;
		}
	}

	res = calloc(((++res_i) + 3), sizeof(*res));
	if (!res)
	{
		perror("Malloc fail");
		return (NULL);
	}

	if (a < b || (a == b && n1[diff] < n2[diff]))
		res[0] = '-';
	else
		res[0] = '0';

	while ((a >= 0 || b >= 0) && res_i > 0)
	{
		if (a > b || (a == b && n1[diff] > n2[diff]))
		{
			if (b >= 0)
				byt_res += ((n1[a] - '0') - (n2[b] - '0'));
			else
				byt_res += (n1[a] - '0');
		}
		else
		{
			if (a >= 0)
				byt_res += ((n2[b] - '0') - (n1[a] - '0'));
			else
				byt_res += (n2[b] - '0');
		}

		if (byt_res < 0 && res_i > 1)
		{
			byt_res += 10;
			res[res_i] = (byt_res % 10) + '0';
			byt_res = -1;
		}
		else
		{
			res[res_i] = abs(byt_res % 10) + '0';
			byt_res = 0;
		}

		--a;
		--b;
		--res_i;
	}

	return (res);
}
