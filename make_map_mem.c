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
	int g = 0;

	fprintf(stdout, "Sizing.......\n");
	if (ftruncate(fd, (MEM_SIZE * ARRAY_SIZE)))
		return (0);

	fprintf(stdout, "Mapping......\n");
	for (g = 0; g < ARRAY_SIZE; g++)
	{
		(*optimus)[g].primes = mmap(NULL, MEM_SIZE, prot_f, modf, fd, (g * B_PAGES));
		if ((*optimus)[g].primes == MAP_FAILED)
			return (0);
	}

	return (1);
}
