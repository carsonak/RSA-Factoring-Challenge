#include "rsaf.h"

/**
 * insert_here - inserts a node after a given node
 * @node: address of the pointer to the node to insert after
 * @num: data for the node
 *
 * Return: pointer to the new node, NULL on error
 */
num_lst *insert_node_here(num_lst **node, u_int64_t num)
{
	num_lst *new;

	if (!node)
		return (NULL);

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);

	new->number = num;

	if (!(*node))
	{
		new->next = NULL;
		*node = new;
		return (new);
	}

	new->next = (*node)->next;
	(*node)->next = new;

	return (new);
}

/**
 * free_list - frees memory of a linked list
 * @head: pointer to the first node
 */
void free_list(num_lst *head)
{
	num_lst *ptr;

	while (head)
	{
		ptr = head;
		head = head->next;
		free(ptr);
	}
}
