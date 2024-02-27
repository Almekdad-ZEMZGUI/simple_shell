#include "s_shell.h"

/**
 * addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @data: data field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
str_list_t *addNode(str_list_t **head, const char *data, int num)
{
	str_list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(str_list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(str_list_t));
	new_node->num = num;

	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * addNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: data field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
str_list_t *addNodeEnd(str_list_t **head, const char *data, int num)
{
	str_list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(str_list_t));

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(str_list_t));
	new_node->num = num;

	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * printStr - prints only the str element of a str_list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printStr(const str_list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->data ? h->data : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * deleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(str_list_t **head, unsigned int index)
{
	str_list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}

	node = *head;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}

		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void freeList(str_list_t **head_ptr)
{
	str_list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}

