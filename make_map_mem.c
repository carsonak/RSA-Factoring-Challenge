#include "rsaf.h"

/**
 * make_mm - assigns shared mapped memory from a file descriptor
 * @optimus: pointer to an array of structures
 * @fd: an open file descriptor
 * @arr_size: size of each block of memory
 *
 * Return: 1 on success, 0 on failure
 */
int make_mm(lock_m **optimus, int fd, int arr_size)
{
	int modf = MAP_SHARED;
	int prot_f = PROT_READ | PROT_WRITE;
	int g = 0;

	fprintf(stdout, "Mapping......\n");
	for (g = 0; g < arr_size; g++)
	{
		(*optimus)[g].primes = mmap(NULL, MEM_SIZE, prot_f, modf, fd, 0);
		if ((*optimus)[g].primes == MAP_FAILED)
			return (0);

		errno = pthread_mutex_init(&(*optimus)[g].mutex, NULL);
		if (errno)
			return (0);
	}

	return (1);
}
