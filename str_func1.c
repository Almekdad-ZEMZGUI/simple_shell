#include "s_shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * _strcmp - comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);

		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _starts_with - checks if needle starts with haystack
 * @haystack: the string
 * @needle: the substring
 *
 * Return: the address of next char of haystack or NULL
 */
char *_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (result);
}

/**
 * _putchar - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1, On error -1 is returned
 */
int _putchar(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (character != BUFFER_FLUSH)
		buffer[index++] = character;

	return (1);
}

