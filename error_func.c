#include "s_shell.h"

/**
 *_eputs - prints an input string
 * @str: the string
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character
 *
 * Return: On success 1, ow -1
 */
int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to The file descriptor
 * @c: The character to print
 * @fd: The file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string
 * @fd: the file descriptor
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfd(*str++, fd);
	}
	return (index);
}

