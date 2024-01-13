#include "rsaf.h"

/**
 * populate - fills a mapped memory with prime numbers
 * @file_des: file descriptor of the mapped memory backing file
 * @g: starting point in multiple of millions
 * @step: steps to skip for concurrency with other processes
 *
 * Return: 1 on success, 0 on failure.
 */
int populate(int file_des, int g, int step)
{
	uint8_t *temp = NULL;
	int64_t h = 0, range = 0, p_idx = 0;
	pf_lock file_lock = {F_WRLCK, SEEK_SET, SV_PG_MEM, PG_MEM, 0};

	for (; g < ARRAY_BLOCKS && !interrupted; g += step)
	{
		errno = 0;
		range = g * A_MILI;
		file_lock.l_type = F_WRLCK;
		file_lock.l_start = SV_PG_MEM + (g * PG_MEM);
		if (fcntl(file_des, F_OFD_SETLKW, &file_lock) == -1)
		{
			perror("File lock not available");
			return (0);
		}

		for (h = range, p_idx = (g * PG_MEM); h < (range + A_MILI) && !interrupted; h++)
		{
			if (sieve[h / 8] & (1 << (h % 8)))
			{
				temp = &optimus[p_idx];
				int_tostr(h, &temp);
				p_idx += 10;
			}
		}

		if (msync(optimus, (PG_MEM * ARRAY_BLOCKS), MS_ASYNC | MS_INVALIDATE) == -1)
		{
			perror("Writing Failed");
			return (0);
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(file_des, F_OFD_SETLKW, &file_lock) == -1)
		{
			perror("File unlock failed");
			return (0);
		}
	}

	return (1);
}

/**
 * int64_tostr - copies a number into a string.
 * @num: the number
 * @str: address of a buffer
 *
 * Return: 1 on success, 0 on failure
 */
int int_tostr(int64_t num, uint8_t **str)
{
	int var = 1, index = 0;

	if (!str || !(*str))
		return (0);

	if (num < 0)
	{
		*str[index] = '-';
		num = -num;
		index++;
	}

	while (num / var >= 10)
		var = var * 10;

	for (index = 0; var > 0; index++)
	{
		(*str)[index] = (num / var) + '0';
		num = num % var;
		var = var / 10;
	}

	(*str)[index] = '\0';
	return (1);
}
