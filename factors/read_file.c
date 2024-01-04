#include "rsaf.h"

/**
 * read_file - opens a file and stores contents in a linked list
 * @file_name: name of the file
 *
 * Return: head of a linked list, NULL on failure
 */
num_lst *read_file(char *file_name)
{
	FILE *file_S = NULL;
	char *line = NULL;
	size_t n = 0;
	ssize_t len = 0;
	num_lst *head = NULL;

	file_S = fopen(file_name, "r");
	if (!file_S)
	{
		perror("Error opening file");
		return (NULL);
	}

	while ((len = getline(&line, &n, file_S)) != -1)
	{
		errno = 0;
		if (!insert_node_end(&head, strtok(line, " \t\n"), len - 1))
		{
			perror("Error creating linked list");
			free_list(head);
			fclose(file_S);
			return (NULL);
		}

		free(line);
		line = NULL;
		n = 0;
	}

	fclose(file_S);
	free(line);
	return (head);
}
