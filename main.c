#include "rsaf.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	u_int64_t *optimus = NULL;
	u_int8_t *sieve = NULL;
	pid_t fk1 = 0;
	int o_flags = O_CREAT | O_RDWR | O_TRUNC, file_des = 0, chld_stat = 0;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;
	char *shared_file = "/prime_map";

	errno = 0;
	file_des = shm_open(shared_file, o_flags, crt_mode);
	if (file_des == -1)
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);

	if (!make_mm(&optimus, file_des))
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);

	sieve = sieve_o_atkins(ARRAY_BLOCKS * A_MILI);
	if (!sieve)
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);

	fk1 = fork();
	if (fk1 == -1)
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);
	else if (fk1 == 0)
	{
		if (!populate(optimus, sieve, file_des, 0, 1))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&chld_stat);
		operate(optimus, file_des);
	}

	free(sieve);
	clean_exit(optimus, EXIT_SUCCESS, file_des, shared_file);
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
