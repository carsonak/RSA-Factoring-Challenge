#include "rsaf.h"

/**
 * make_mm - assigns shared mapped memory from a file descriptor
 * @optimus: address of a pointer
 * @shared_file: name of the shared file to create
 *
 * Return: a file descriptor on success, -1 on failure
 */
int make_mm(size_t **optimus, char *shared_file)
{
	int modf = MAP_SHARED;
	int prot_f = PROT_READ | PROT_WRITE;
	int o_flags = O_CREAT | O_RDWR | O_TRUNC, file_des = 0;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;

	file_des = shm_open(shared_file, o_flags, crt_mode);
	if (file_des != -1)
	{

		if (ftruncate(file_des, (PG_MEM * ARRAY_BLOCKS)))
			return (-1);

		*optimus = mmap(NULL, (PG_MEM * ARRAY_BLOCKS), prot_f, modf, file_des, 0);
		if (*optimus == MAP_FAILED)
			return (-1);
	}

	return (file_des);
}
