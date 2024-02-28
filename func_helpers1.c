#include "s_shell.h"

/**
 * check_interactive_mode - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readFd <= 2);
}

/**
 * is_character_delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_character_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha_character - checks for alphabetic character
 * @c: The character
 * Return: 1 if c is alphabetic, otherwise 0
 */
int is_alpha_character(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, otherwise converted number
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, result;
	unsigned int out = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			out *= 10;
			out += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -out;
	else
		result = out;

	return (result);
}

/**
 * erase_comments - function replaces instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: nothing
 */
void erase_comments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

