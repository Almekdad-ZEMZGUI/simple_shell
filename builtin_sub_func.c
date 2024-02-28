#include "s_shell.h"

/**
 * remove_alias - removes an alias from the list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign, char_placeholder;
	int ret;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);

	char_placeholder = *equal_sign;
	*equal_sign = 0;

	ret = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, node_starts_with(info->alias, str, -1)));

	*equal_sign = char_placeholder;
	return (ret);
}

/**
 * assign_alias - assigns an alias to a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int assign_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (addNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - displays an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *equal_sign, *alias;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

