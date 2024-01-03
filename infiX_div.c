#include "infix.h"

uint8_t *remain = NULL;

/**
 * infiX_div - divides a string on numbers
 * @dividend: dividend
 * @divisor: divisor
 *
 * Description: this function also stores the remainder on any division
 * in a global variable "remain". This memory should be freed and reset
 * NULL before the next call of this function.
 *
 * Return: string with the result, NULL on failure
 */
uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor)
{
	size_t len_dend = strlen((char *)dividend), len_sor = strlen((char *)divisor);
	size_t len_rem = 0, nd = 0, q = 0, len_q = 0, byte_dend = 0;
	uint8_t *quotient = NULL, *temp = NULL, *new_r = NULL;

	if (len_dend < len_sor || !len_sor || (len_dend == 1 && dividend[0] == '0'))
	{
		remain = calloc(len_dend + 1, sizeof(*remain));
		if (!remain)
		{
			perror("Malloc fail");
			return (NULL);
		}

		strcpy((char *)remain, (char *)dividend);
		return (NULL);
	}
	else if (len_sor == 1 && divisor[0] == '0')
		return (NULL);

	len_q = (len_dend - len_sor) + 1;
	quotient = calloc(len_q + 2, sizeof(*quotient));
	remain = calloc((len_dend > len_sor ? len_dend : len_sor) + 1, sizeof(*remain));
	if (!quotient || !remain)
	{
		perror("Malloc fail");
		return (NULL);
	}

	strncpy((char *)remain, (char *)dividend, len_sor);
	nd = len_sor;
	len_rem = strlen((char *)remain);
	for (q = 0; q < len_q && nd <= len_dend; q++)
	{
		errno = 0;
		if (len_rem < len_sor)
		{
			for (; q < len_q && len_rem < len_sor; q++, nd++, len_rem++)
			{
				remain[len_rem] = dividend[nd];
				quotient[q] = '0';
			}
		}

		remain[len_rem] = '\0';
		if (len_rem > len_sor)
		{
			byte_dend = strtonul((char *)remain, 2);
			quotient[q] = (byte_dend / (divisor[0] - '0')) + '0';
		}
		else
			quotient[q] = ((remain[0] - '0') / (divisor[0] - '0')) + '0';

		while (!new_r || (new_r[0] == '-' && quotient[q] > '0'))
		{
			if (new_r && new_r[0] == '-' && quotient[q] > '0')
				quotient[q] -= 1;

			free(temp);
			free(new_r);
			temp = NULL;
			new_r = NULL;
			temp = infiX_mul(divisor, &quotient[q]);
			if (temp)
			{
				new_r = infiX_sub(remain, temp);
				if (!new_r)
				{
					perror("Malloc fail");
					return (NULL);
				}
			}
			else
			{
				perror("Malloc fail");
				return (NULL);
			}
		}

		strcpy((char *)remain, (char *)(&new_r[pad_char((char *)new_r, "0")]));

		len_rem = strlen((char *)remain);
		remain[len_rem] = dividend[nd];
		len_rem++;
		nd++;
		remain[len_rem] = '\0';

		free(new_r);
		free(temp);
		temp = NULL;
		new_r = NULL;
	}

	return (quotient);
}
