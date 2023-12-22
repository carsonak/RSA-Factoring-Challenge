#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: pointer to the mapped memory
 * @shared_fd: file descriptor of the backing file
 * @tofactor: path to file
 *
 * Return: 0 on failure, 1 on success
 */
int operate(u_int64_t *optimus, int shared_fd, char *tofactor)
{
	FILE *tofactor_S = NULL;
	char *line = NULL;
	size_t n = 0;
	ssize_t len = 0;
	u_int64_t num = 0, factor = 0;
	num_lst *head = NULL, *walk = head;

	tofactor_S = fopen(tofactor, "r");
	if (!tofactor_S)
		return (0);

	while ((len = getline(&line, &n, tofactor_S)) != -1)
	{
		errno = 0;
		if (len < 18)
		{
			num = strtoll(line, NULL, 10);
			for (walk = head; head && walk->next; walk = walk->next)
				if (num < walk->next->number)
					break;

			if (!insert_node_here(&walk, num))
			{
				free_list(head);
				fclose(tofactor_S);
				return (0);
			}

			head = !(head) ? walk : head;
		}
		else
		{
			/* code */
		}

		free(line);
		line = NULL;
		n = 0;
	}

	if (feof(tofactor_S))
	{
		walk = head;
		while (walk)
		{
			factor = factorise(optimus, walk->number, shared_fd);
			if (!factor && errno)
				break;
			else if (!factor && !errno)
			{
				/* code */
			}
			else
				printf("%ld=%ld*%ld\n", walk->number, (walk->number / factor), factor);

			walk = walk->next;
		}
	}
	else
	{
		free_list(head);
		fclose(tofactor_S);
		return (0);
	}

	free_list(head);
	fclose(tofactor_S);
	return (1);
}
