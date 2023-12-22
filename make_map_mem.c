#include "rsaf.h"

/**
 * make_mm - assigns shared mapped memory from a file descriptor
 * @optimus: address of a pointer
 * @fd: an open file descriptor
 *
 * Return: 1 on success, 0 on failure
 */
int make_mm(size_t **optimus, int fd)
{
	int modf = MAP_SHARED;
	int prot_f = PROT_READ | PROT_WRITE;

	if (ftruncate(fd, (PG_MEM * ARRAY_BLOCKS)))
		return (0);

	*optimus = mmap(NULL, (PG_MEM * ARRAY_BLOCKS), prot_f, modf, fd, 0);
	if (*optimus == MAP_FAILED)
		return (0);

	return (1);
}
