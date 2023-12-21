#include "rsaf.h"

/**
 * populate - fills a mapped memory with prime numbers
 * @optimus: array of structures with pointers to mapped memory locations on the file
 * @file_des: file descriptor of the backing file
 * @start: index of the array used as starting point
 * @step: steps to skip in order to coordinate with other processes
 *
 * Return: 1 on success, 0 on failure.
 */
int populate(lock_m optimus[], int file_des, int start, int step)
{
	size_t g = 0, h = 0, count = 0;
	int *sieve = NULL;
	pf_lock file_lock = {F_WRLCK, SEEK_SET, 0, PG_MEM, getpid()};

	for (g = start; g < ARRAY_BLOCKS; g += step)
	{
		errno = 0;
		file_lock.l_type = F_WRLCK;
		file_lock.l_start = (off_t)(g * PG_MEM);
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			return (0);
		}

		sieve = sieve_o_atkins((g * A_MILI), A_MILI);
		if (!sieve)
			return (0);

		for (h = 0, count = 0; h < A_MILI && count < NODES; h++)
		{
			if (sieve[h])
			{
				optimus[g].primes[count] = (g * A_MILI) + h;
				count++;
			}
		}

		if (msync(optimus[g].primes, NODES_MEM, MS_ASYNC | MS_INVALIDATE))
		{
			perror("Writing Failed");
			return (0);
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			return (0);
		}

		free(sieve);
	}

	return (1);
}

/**
 * sieve_o_atkins - generates a sieve to find prime numbers in a range
 * @start: starting number
 * @range: the range
 *
 * Return: a sieve, NULL on failure
 */
int *sieve_o_atkins(size_t start, size_t range)
{
	ssize_t limit = start + range, wlimit = 0, start_i = 0;
	ssize_t i, j, x, y, z;
	int *sieb = NULL;

	sieb = calloc(range, sizeof(*sieb));
	if (!sieb)
	{
		perror("Block alocation failed\n");
		return (NULL);
	}

	wlimit = sqrt(limit);
	if (!start)
	{
		sieb[1] = 1;
		sieb[2] = 1;
		sieb[4] = 1;
		i = 5;
	}
	else
	{
		start_i = sqrt(start - 1);
		i = 0;
	}

	for (x = start_i; x <= wlimit; x++)
	{
		for (y = start_i; y <= wlimit; y++)
		{
			z = (4 * x * x) + (y * y);

			if (z <= limit &&
				(z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
				 z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
				sieb[z] = 1;

			z = (3 * x * x) + (y * y);

			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
				sieb[z] = 1;

			z = (3 * x * x) - (y * y);

			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
				sieb[z] = 1;
		}
	}

	for (; i <= wlimit; i++)
		if (sieb[i] == 1)
			for (j = 1; j * i * i <= limit; j++)
				sieb[j * i * i] = 0;

	return (sieb);
}
