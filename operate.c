#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: pointer to the mapped memory
 * @file_des: file descriptor of the backing file
 */
void operate(size_t *optimus, int file_des)
{
	u_int64_t g = 0, h = 0;
	pf_lock file_lock = {F_RDLCK, SEEK_SET, 0, PG_MEM, 0};

	for (g = 0; g < ARRAY_BLOCKS; g++)
	{
		errno = 0;
		file_lock.l_type = F_RDLCK;
		file_lock.l_start = (off_t)(g * PG_MEM);
		file_lock.l_pid = 0;
		if (fcntl(file_des, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			continue;
		}

		for (h = 0; optimus[h + (g * NODE_SZ)]; h++)
		{
			if (!(h % 16) && h > 1)
				putchar('\n');

			printf("%5ld ", optimus[h + (g * NODE_SZ)]);
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(file_des, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			return;
		}
	}

	putchar('\n');
}
