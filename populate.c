#include "rsaf.h"

/**
 * populate - fills a mapped memory with prime numbers
 * @optimus: pointer to the mapped memory
 * @file_des: file descriptor of the backing file
 * @range: max range in millions
 *
 * Return: 1 on success, 0 on failure.
 */
int populate(size_t *optimus, int file_des, size_t range)
{
	size_t h = 0, count = 0;
	char *sieve = NULL;
	pf_lock file_lock = {F_WRLCK, SEEK_SET, 0, (PG_MEM * range), getpid()};

	errno = 0;
	if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
	{
		perror("File lock not available");
		return (0);
	}

	sieve = sieve_o_atkins(range * A_MILI);
	if (!sieve)
		return (0);

	for (h = 0, count = 0; h < (range * A_MILI); h++)
	{
		if (sieve[h])
		{
			optimus[count] = h;
			count++;
		}
	}

	if (msync(optimus, (range * PG_MEM), MS_ASYNC | MS_INVALIDATE))
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
	return (1);
}

/**
 * sieve_o_atkins - generates a sieve to find prime numbers in a range
 * @range: the range
 *
 * Return: a sieve, NULL on failure
 */
char *sieve_o_atkins(size_t range)
{
	ssize_t limit = range, ulimit = 0;
	ssize_t i, j, x, y, z;
	char *sieb = NULL;

	sieb = calloc(range, sizeof(*sieb));
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
				sieb[z] = !sieb[z];

			z = (3 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
				sieb[z] = !sieb[z];

			z = (3 * x * x) - (y * y);
			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
				sieb[z] = !sieb[z];
		}
	}

	sieb[2] = !sieb[2];
	sieb[3] = !sieb[3];
	sieb[5] = !sieb[5];
	for (i = 5; i <= ulimit; i++)
		if (sieb[i] == 1)
			for (j = 1; (j * i * i) <= limit; j++)
				sieb[(j * i * i)] = 0;

	return (sieb);
}
