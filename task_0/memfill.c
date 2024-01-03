#include "infix.h"

/**
 * memfill - fills a section of memory with a constant byte
 * @mem: pointer to a memory block
 * @b: character to fill memory with
 * @start: where to start filling
 * @nbytes: how many bytes to fill
 *
 * Return: pointer to the modified memory block
 */
void *memfill(void *mem, char b, size_t start, size_t nbytes)
{
	size_t i = 0;

	for (i = start; i < (start + nbytes); i++)
		((char *)mem)[i] = b;

	return (mem);
}
