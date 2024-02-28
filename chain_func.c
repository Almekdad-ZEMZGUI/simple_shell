#include "s_shell.h"

/**
 * isCommandChain - test if the current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isCommandChain(info_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		info->commandBufferType = COMMAND_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		info->commandBufferType = COMMAND_AND;
	}
	else if (buffer[index] == ';')
	{
		buffer[index] = 0;
		info->commandBufferType = COMMAND_CHAIN;
	}
	else
		return (0);
	*position = index;
	return (1);
}

/**
 * checkChain - checks if should continue chaining
 * @info: the parameter struct
 * @buf: the char buffer
 * @pos: address of current position
 * @i: starting index
 * @l: length of buffer
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buf, size_t *pos, size_t i, size_t l)
{
	size_t index = *pos;

	if (info->commandBufferType == COMMAND_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			index = l;
		}
	}
	if (info->commandBufferType == COMMAND_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			index = l;
		}
	}

	*pos = index;
}

/**
 * replaceAliases - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
	int i;
	str_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodePrefix(info->alias, info->arguments[0], '=');
		if (!node)
			return (0);
		free(info->arguments[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->arguments[0] = p;
	}
	return (1);
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
	int i = 0;
	str_list_t *node;

	for (i = 0; info->arguments[i]; i++)
	{
		if (info->arguments[i][0] != '$' || !info->arguments[i][1])
			continue;

		if (!_strcmp(info->arguments[i], "$?"))
		{
			replaceString(&(info->arguments[i]),
				_strdup(convert_to_string(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->arguments[i], "$$"))
		{
			replaceString(&(info->arguments[i]),
				_strdup(convert_to_string(getpid(), 10, 0)));
			continue;
		}
		node = nodePrefix(info->environment, &info->arguments[i][1], '=');
		if (node)
		{
			replaceString(&(info->arguments[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->arguments[i], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replaces string
 * @oldString: address of old string
 * @newString: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}




