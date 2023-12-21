#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: array of structs with the mapped memory
 * @arr_sz: size of the array
 * @file_des: file descriptor of the backing file
 */
void operate(lock_m optimus[], size_t arr_sz, int file_des)
{
	size_t g = 0, h = 0;
	pf_lock file_lock = {F_RDLCK, SEEK_SET, 0, PG_MEM, getpid()};

	for (g = 0; g < arr_sz; g++)
	{
		errno = 0;
		file_lock.l_type = F_RDLCK;
		file_lock.l_start = (off_t)(g * PG_MEM);
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			continue;
		}

		for (h = 0; (optimus[g].primes[h] > 0); h++)
		{
			printf("%5ld ", optimus[g].primes[h]);
			if (!(h % 16))
				putchar('\n');
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(file_des, F_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			return;
		}
	}
}
