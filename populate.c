#include "rsaf.h"

/**
 * populate - fills a mapped memory with prime numbers
 * @optimus: pointer to a mapped memory
 * @sieve: a bit mask sieve for prime numbers within a limit
 * of ARRAY_BLOCKS * A_MILI
 * @file_des: file descriptor of the mapped memory backing file
 * @g: starting point in multiple of millions
 * @step: steps to skip for concurrency with other processes
 *
 * Return: 1 on success, 0 on failure.
 */
int populate(uint64_t *optimus, u_int8_t *sieve, int file_des, int g, int step)
{
	uint64_t range = 0, h = 0, count = 0;
	pf_lock file_lock = {F_WRLCK, SEEK_SET, 0, PG_MEM, 0};

	for (; g < ARRAY_BLOCKS; g += step)
	{
		errno = 0;
		range = g * A_MILI;
		file_lock.l_type = F_WRLCK;
		file_lock.l_start = g * PG_MEM;
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			free(sieve);
			return (0);
		}

		for (h = range, count = (g * NODE_SZ); h < (range + A_MILI); h++)
		{
			if (sieve[h / 8] & (1 << (h % 8)))
			{
				optimus[count] = h;
				count++;
			}
		}

		if (msync(optimus + (g * NODE_SZ), PG_MEM, MS_SYNC | MS_INVALIDATE))
		{
			perror("Writing Failed");
			free(sieve);
			return (0);
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			free(sieve);
			return (0);
		}
	}

	free(sieve);
	return (1);
}
