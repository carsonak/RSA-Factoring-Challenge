#include "rsaf.h"
#include "infix.h"

/**
 * factorise - finds the smallest factor of a number
 * @num: the number to factorise
 * @big_fct: address of a pointer to the patner factor
 * @shared_fd: file descriptor of shared memory
 *
 * Return: a factor of the number, NULL on failure or if not found
 */
uint8_t *factorise(uint8_t *num, uint8_t **big_fct, int shared_fd)
{
	uint64_t g = 0, h = 0;
	pf_lock file_lock = {F_RDLCK, SEEK_SET, SV_PG_MEM, PG_MEM, 0};

	for (g = 0; g < ARRAY_BLOCKS && !interrupted; g++)
	{
		errno = 0;
		file_lock.l_type = F_RDLCK;
		file_lock.l_start = SV_PG_MEM + (g * PG_MEM);
		if (fcntl(shared_fd, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			return (NULL);
		}

		for (h = 0; optimus[(g * PG_MEM) + (h * 10)] && !interrupted; h++)
		{
			remain = NULL;
			*big_fct = (u_int8_t *)infiX_op((char *)num, "/", (char *)&optimus[(g * PG_MEM) + (h * 10)]);
			if (!big_fct)
			{
				free(remain);
				return (NULL);
			}

			if (remain && remain[0] == 1 && remain[1] == 0)
			{
				free(remain);
				break;
			}

			free(remain);
			free(*big_fct);
			*big_fct = NULL;
		}

		file_lock.l_type = F_UNLCK;
		if (fcntl(shared_fd, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File unlock failed");
			return (NULL);
		}

		if (optimus[(g * PG_MEM) + (h * 10)])
			return (&optimus[(g * PG_MEM) + (h * 10)]);
	}

	return (NULL);
}
