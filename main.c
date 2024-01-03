#include "rsaf.h"

uint8_t *sieve = NULL, *optimus = NULL;

/**
 * main - entry point
 * @argc: number of arguments passed
 * @argv: array of the commands
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
	num_lst *head = NULL;
	pid_t fk1 = 0;
	int shared_fd = 0, chld_stat = 0;
	char *shared_file = "/prime_map";

	errno = 0;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: factors <file>\n");
		return (EXIT_FAILURE);
	}

	shared_fd = make_mm(shared_file);
	if (shared_fd == -1)
		clean_exit(shared_fd, shared_file, head, EXIT_FAILURE);

	if (!sieve_o_atkins(ARRAY_BLOCKS * A_MILI))
		clean_exit(shared_fd, shared_file, head, EXIT_FAILURE);

	fk1 = fork();
	if (fk1 == -1)
		clean_exit(shared_fd, shared_file, head, EXIT_FAILURE);
	else if (fk1 == 0)
	{
		if (!populate(shared_fd, 0, 1))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}

	waitpid(fk1, &chld_stat, WNOHANG);
	head = read_file(argv[1]);
	if (!head)
		clean_exit(shared_fd, shared_file, head, EXIT_FAILURE);

	if (!operate(head, shared_fd))
		clean_exit(shared_fd, shared_file, head, EXIT_FAILURE);

	clean_exit(shared_fd, shared_file, head, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

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

	if (status == EXIT_FAILURE)
	{
		perror("FAILED");
		errno = 0;
		exit(EXIT_FAILURE);
	}
}
