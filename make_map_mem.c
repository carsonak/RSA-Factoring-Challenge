#include "rsaf.h"

/**
 * make_mm - assigns shared mapped memory from a file descriptor
 * @optimus: pointer to an array of structures
 * @fd: an open file descriptor
 *
 * Return: 1 on success, 0 on failure
 */
int make_mm(lock_m **optimus, int fd)
{
	int modf = MAP_SHARED;
	int prot_f = PROT_READ | PROT_WRITE;
	off_t g = 0;

	if (ftruncate(fd, (off_t)(PG_MEM * ARRAY_BLOCKS)))
		return (0);

	for (g = 0; g < ARRAY_BLOCKS; g++)
	{
		(*optimus)[g].primes = mmap(NULL, (size_t)PG_MEM, prot_f, modf, fd, (g * PG_MEM));
		if ((*optimus)[g].primes == MAP_FAILED)
			return (0);
	}

	(*optimus)[g].primes = NULL;
	return (1);
}
