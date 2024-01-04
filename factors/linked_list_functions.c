#include "rsaf.h"

/**
 * insert_here - inserts a node after a given node
 * @here: address of the pointer to the node to insert after
 * @numstr: content to be added
 * @numlen: content to be added
 *
 * Return: pointer to the new node, NULL on error
 */
num_lst *insert_node_here(num_lst **here, char *numstr, size_t numlen)
{
	num_lst *new;

	if (!here)
		return (NULL);

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);

	new->len = numlen;
	strcpy((char *)new->number, numstr);

	if (!(*here))
	{
		new->next = NULL;
		*here = new;
		return (new);
	}

	new->next = (*here)->next;
	(*here)->next = new;

	return (new);
}

/**
 * add_nodeint_end - adds a node to the end of a linked list
 * @head: pointer to the head of the list
 * @numstr: content to be added
 * @numlen: content to be added
 *
 * Return: the address of the new node on success, NULL on failure
 */
num_lst *insert_node_end(num_lst **head, char *numstr, size_t numlen)
{
	num_lst *new_node;
	num_lst *ptr = *head;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(num_lst));
	if (!new_node)
		return (NULL);

	new_node->len = numlen;
	strcpy((char *)new_node->number, numstr);
	new_node->next = NULL;

	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;

		ptr->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
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
