#include "rsaf.h"
#include "infix.h"

/**
 * clean_exit - unmaps and unlinks shared memory
 * @fd: an open shared file descriptor
 * @shared_file: shared file name
 * @head: pointer to head of a linked list
 * @status: exit status
 */
void clean_exit(int fd, char *shared_file, num_lst *head, int status)
{
	munmap(sieve, SV_PG_MEM);
	munmap(optimus, (PG_MEM * ARRAY_BLOCKS));
	if (fd != -1)
		shm_unlink(shared_file);

	if (head)
		free_list(head);

	if (errno)
	{
		perror("FAILED");
		errno = 0;
	}

	if (status == EXIT_FAILURE)
		exit(EXIT_FAILURE);
}
