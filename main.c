#include "rsaf.h"

/**
 * main - entry point
 * @argc: number of arguments passed
 * @argv: array of the caommands
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
	u_int64_t *optimus = NULL;
	u_int8_t *sieve = NULL;
	pid_t fk1 = 0, fk2 = 0, fk3 = 0;
	int shared_fd = 0, chld_stat = 0;
	char *shared_file = "/prime_map";

	errno = 0;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: factors <file>\n");
		return (EXIT_FAILURE);
	}

	shared_fd = make_mm(&optimus, shared_file);
	if (shared_fd == -1)
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);

	sieve = sieve_o_atkins(ARRAY_BLOCKS * A_MILI);
	if (!sieve)
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);

	fk1 = fork();
	if (fk1 == -1)
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);
	else if (fk1 == 0)
	{
		if (!populate(optimus, sieve, shared_fd, 0, 3))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}

	waitpid(fk1, &chld_stat, WNOHANG);
	fk2 = fork();
	if (fk2 == -1)
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);
	else if (fk2 == 0)
	{
		if (!populate(optimus, sieve, shared_fd, 1, 3))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}

	waitpid(fk2, &chld_stat, WNOHANG);
	fk3 = fork();
	if (fk3 == -1)
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);
	else if (fk3 == 0)
	{
		if (!populate(optimus, sieve, shared_fd, 2, 3))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}

	waitpid(fk3, &chld_stat, WNOHANG);
	if (!operate(optimus, shared_fd, argv[1]))
	{
		free(sieve);
		clean_exit(optimus, EXIT_FAILURE, shared_fd, shared_file);
	}

	free(sieve);
	clean_exit(optimus, EXIT_SUCCESS, shared_fd, shared_file);
	return (EXIT_SUCCESS);
}

/**
 * clean_exit - uninks shared memory and destroys mutex
 * @optimus: structures with the shard mem and mutexes
 * @status: exit status
 * @fd: an open file descriptor
 * @shared_file: shared file
 */
void clean_exit(size_t *optimus, int status, int fd, char *shared_file)
{
	munmap(optimus, (PG_MEM * ARRAY_BLOCKS));
	if (fd != -1)
		shm_unlink(shared_file);

	if (status == EXIT_FAILURE)
	{
		perror("FAILED");
		exit(EXIT_FAILURE);
	}
}
