#include "rsaf.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	lock_m optimus[ARRAY_SIZE];
	pid_t fk1 = 0, fk2 = 0;
	int o_flags = O_CREAT | O_RDWR | O_TRUNC, filedes = 0, wait_stat;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;
	char *shared_file = "/prime_map";
	lock_m *bumble = optimus;

	errno = 0;
	filedes = shm_open(shared_file, o_flags, crt_mode);
	if (filedes == -1)
		clean_exit(optimus, EXIT_FAILURE, filedes, shared_file);

	if (!make_mm(&bumble, filedes))
		clean_exit(optimus, EXIT_FAILURE, filedes, shared_file);

	fk1 = fork();
	if (fk1 == -1)
		clean_exit(optimus, EXIT_FAILURE, filedes, shared_file);
	else if (fk1 == 0)
	{
		populate(optimus);
		// fprintf(stdout, "FK1 is done\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&wait_stat);
		fk2 = fork();
		if (fk2 == 0)
		{
			// fprintf(stdout, "FK2 is done\n");
			exit(EXIT_SUCCESS);
		}
		else
			operate(optimus, ARRAY_SIZE);
	}

	clean_exit(optimus, EXIT_SUCCESS, filedes, shared_file);
	// printf("B_PAGES %ld\n", B_PAGES);
	//  fprintf(stdout, "SUPER is done\n");
	return (EXIT_SUCCESS);
}

/**
 * clean_exit - uninks shared memory and destroys mutex
 * @optimus: structures with the shard mem and mutexes
 * @status: exit status
 * @fd: an open file descriptor
 * @file_name: shared file
 */
void clean_exit(lock_m optimus[], int status, int fd, char *file_name)
{
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		if (optimus[i].primes)
			munmap(optimus[i].primes, MEM_SIZE);
		else
			break;
	}

	if (fd != -1)
		shm_unlink(file_name);

	if (status)
	{
		perror("FAILED");
		exit(EXIT_FAILURE);
	}
}
