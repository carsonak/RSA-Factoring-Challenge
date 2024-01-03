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
	uint64_t g = 0, h = 0, max = 0;
	uint8_t *temp = NULL;
	pf_lock file_lock = {F_RDLCK, SEEK_SET, SV_PG_MEM, PG_MEM, 0};

	temp = infiX_div(infiX_div(num, (uint8_t *)"2"), (uint8_t *)"1000000");
	if (!temp && !errno)
		max = 0;
	else if (temp)
		max = (uint64_t)strtol((char *)temp, NULL, 10);
	else
	{
		free(remain);
		return (NULL);
	}

	for (g = 0; g < max + 1 && g < ARRAY_BLOCKS; g++)
	{
		errno = 0;
		file_lock.l_type = F_RDLCK;
		file_lock.l_start = SV_PG_MEM + (g * PG_MEM);
		if (fcntl(shared_fd, F_OFD_SETLKW, &file_lock, NULL) == -1)
		{
			perror("File lock not available");
			return (NULL);
		}

		for (h = 0; optimus[(g * PG_MEM) + h]; h += 10)
		{
			remain = NULL;
			*big_fct = infiX_div(num, &optimus[(g * PG_MEM) + h]);
			if (errno)
			{
				free(remain);
				return (NULL);
			}

			if (remain && remain[pad_char((char *)remain, "0")] == '0')
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

		if (optimus[(g * PG_MEM) + h])
			return (&optimus[(g * PG_MEM) + h]);
	}

	return (NULL);
}
