#include "rsaf.h"
#include "infix.h"

/**
 * operate - print out some data from mapped memory
 * @head: pointer to a linked list
 * @shared_fd: file descriptor of the backing file
 *
 * Return: 0 on failure, 1 on success
 */
int operate(num_lst *head, int shared_fd)
{
	uint8_t *big_factor = NULL, *sml_factor = NULL;
	num_lst *walk = head;
	char *out_put = NULL;

	while (walk && !interrupted)
	{
		errno = 0;
		if (walk->len < 256)
		{
			sml_factor = factorise(walk->number, &big_factor, shared_fd);
			if (errno)
			{
				free(big_factor);
				return (0);
			}
			else if (!sml_factor && !errno)
				printf("%s=%s*%s FAIL\n", walk->number, walk->number, "1");
			else
			{
				out_put = stringscat(6, (char *)walk->number, "=", (char *)&big_factor[pad_char((char *)big_factor, "0")], "*", (char *)sml_factor, "\n");
				if (out_put)
				{
					if (write(STDOUT_FILENO, out_put, strlen(out_put)) == -1)
					{
						free(out_put);
						free(big_factor);
						return (0);
					}
				}
				else
				{
					free(big_factor);
					return (0);
				}

				/*printf("%s=%s*%s\n", walk->number, &big_factor[pad_char((char *)big_factor, "0")], sml_factor);*/
			}

			free(out_put);
			free(big_factor);
			big_factor = NULL;
			out_put = NULL;
		}
		else
			printf("%s=%s*%s FAIL\n", walk->number, walk->number, "1");

		walk = walk->next;
	}

	return (1);
}
