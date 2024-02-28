#include "s_shell.h"

/**
 * listLen - counts length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t listLen(const str_list_t *head)
{
	size_t length = 0;

	while (head)
	{
		head = head->next;
		length++;
	}
	return (length);
}

/**
 * listToString - returns an array of strings of the linked list
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToString(str_list_t *head)
{
	str_list_t *node = head;
	size_t length = listLen(head), j;
	char **result;
	char *str;

	if (!head || !length)
		return (NULL);
	result = malloc(sizeof(char *) * (length + 1));
	if (!result)
		return (NULL);
	for (length = 0; node; node = node->next, length++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < length; j++)
				free(result[j]);
			free(result);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		result[length] = str;
	}
	result[length] = NULL;
	return (result);
}


/**
 * printList - prints all elements of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const str_list_t *head)
{
	size_t length = 0;

	while (head)
	{
		_puts(convert_to_string(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		length++;
	}
	return (length);
}

/**
 * node_prefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pre: string to match
 * @c: nrxt character after match prefix
 *
 * Return: last node, or null
 */
str_list_t *nodePrefix(str_list_t *node, char *pre, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = _starts_with(node->str, pre);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to head
 * @node: pointer to the node
 *
 * Return: index of the node, or -1 on failure
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}


