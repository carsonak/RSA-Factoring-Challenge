#include "rsaf.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	lock_m optimus[(ARRAY_BLOCKS + 1)];
	lock_m *bumble = optimus;
	pid_t fk1 = 0;
	int o_flags = O_CREAT | O_RDWR | O_TRUNC, file_des = 0, chld_stat = 0;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;
	char *shared_file = "/prime_map";

	errno = 0;
	file_des = shm_open(shared_file, o_flags, crt_mode);
	if (file_des == -1)
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);

	if (!make_mm(&bumble, file_des))
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);

	fk1 = fork();
	if (fk1 == -1)
		clean_exit(optimus, EXIT_FAILURE, file_des, shared_file);
	else if (fk1 == 0)
	{
		chld_stat = populate(optimus, file_des, 0, 1);
		if (chld_stat)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		wait(&chld_stat);
		operate(optimus, ARRAY_BLOCKS, file_des);
	}

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
void clean_exit(lock_m optimus[], int status, int fd, char *shared_file)
{
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		if (optimus[i].primes)
			munmap(optimus[i].primes, PG_MEM);
		else
			break;
	}

	if (fd != -1)
		shm_unlink(shared_file);

	if (status == EXIT_FAILURE)
	{
		perror("FAILED");
		exit(EXIT_FAILURE);
	}
}
