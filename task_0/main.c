#include "rsaf.h"

uint8_t *sieve = NULL, *optimus = NULL;
volatile sig_atomic_t interrupted = 0;

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
	struct sigaction grace;

	grace.sa_handler = graceful;
	grace.sa_flags = SA_RESTART;
	if (sigaction(SIGTERM, &grace, NULL) == -1 || sigaction(SIGINT, &grace, NULL) == -1)
		return (EXIT_FAILURE);

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
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
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
 * graceful - signal handler for interrupt and terminate
 * @thesignal:
 */
void graceful(int thesignal)
{
	if (thesignal == SIGINT || thesignal == SIGTERM)
		interrupted = 1;
}
