#include "rsaf.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	lock_m optimus[5];
	pid_t pid = 0;
	int o_flags = O_CREAT | O_RDWR | O_TRUNC, filedes = 0;
	mode_t crt_mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP;
	lock_m *bumble = optimus;

	errno = 0;
	filedes = open("./prime_map", o_flags, crt_mode);
	if (filedes == -1)
		clean_exit(optimus, EXIT_FAILURE, filedes);

	if (!make_mm(&bumble, filedes, 5))
		clean_exit(optimus, EXIT_FAILURE, filedes);

	fprintf(stderr, "Forking......\n");
	pid = fork();
	if (pid == -1)
		clean_exit(optimus, EXIT_FAILURE, filedes);
	else if (pid == 0)
	{
		populate(optimus);
		exit(EXIT_SUCCESS);
	}
	else
		operate(optimus);

	clean_exit(optimus, EXIT_SUCCESS, filedes);
	return (EXIT_SUCCESS);
}

/**
 * clean_exit - uninks shared memory and destroys mutex
 * @optimus: structures with the shard mem and mutexes
 * @status: exit status
 * @fd: an open file descriptor
 */
void clean_exit(lock_m optimus[], int status, int fd)
{
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		if (optimus[i].primes)
			munmap(optimus[i].primes, MEM_SIZE);
		else
			break;

		pthread_mutex_destroy(&optimus[i].mutex);
	}

	if (fd != -1)
		close(fd);

	if (status)
	{
		perror("FAILED");
		exit(EXIT_FAILURE);
	}
}
