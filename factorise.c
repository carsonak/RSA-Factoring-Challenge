#include "rsaf.h"

/**
 * factorise - finds the smallest factor of a number
 * @optimus: a list of primes
 * @num: the num
 * @shared_fd: file descriptor of shared memory
 *
 * Return: a factor of the number, 0 on failure or if not found
 */
u_int64_t factorise(u_int64_t *optimus, u_int64_t num, int shared_fd)
{
	u_int64_t g = 0, h = 0;
	pf_lock file_lock = {F_RDLCK, SEEK_SET, 0, PG_MEM, 0};

	for (g = 0; g < ARRAY_BLOCKS; g++)
	{
		errno = 0;
		file_lock.l_type = F_RDLCK;
		file_lock.l_start = (off_t)(g * PG_MEM);
		file_lock.l_pid = 0;
		if (fcntl(shared_fd, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			return (0);
		}

		for (h = 0; optimus[h + (g * NODE_SZ)]; h++)
			if (!(num % optimus[h + (g * NODE_SZ)]))
				break;

		file_lock.l_type = F_UNLCK;
		if (fcntl(shared_fd, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			return (0);
		}

		if (optimus[h + (g * NODE_SZ)])
			return (optimus[h + (g * NODE_SZ)]);
		else if (optimus[(h - 1) + (g * NODE_SZ)] > sqrt(num))
			return (0);
	}

	return (0);
}
