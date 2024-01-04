#include "rsaf.h"

/**
 * make_mm - create a mapped memory region
 * @shared_file: name of the shared file to create
 *
 * Description: This function opens a file for memory mapping
 * and truncates it to the right size. It then maps two regions
 * of different sizes, one after the other, to some global pointers.
 *
 * Return: a file descriptor on success, -1 on failure
 */
int make_mm(char *shared_file)
{
	/*For opening the file*/
	int file_des = 0, o_flags = O_CREAT | O_RDWR | O_TRUNC;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;
	/*For mapping memory*/
	int prot_f = PROT_READ | PROT_WRITE, mod_f = MAP_SHARED;
	off_t sieve_mem = SV_PG_MEM, prime_mem = PG_MEM * ARRAY_BLOCKS;

	file_des = shm_open(shared_file, o_flags, crt_mode);
	if (file_des != -1)
	{

		if (ftruncate(file_des, sieve_mem + prime_mem))
			return (-1);

		sieve = mmap(NULL, sieve_mem, prot_f, mod_f, file_des, 0);
		if (sieve == MAP_FAILED)
			return (-1);

		optimus = mmap(NULL, prime_mem, prot_f, mod_f, file_des, sieve_mem);
		if (optimus == MAP_FAILED)
			return (-1);
	}

	return (file_des);
}
