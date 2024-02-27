#include "s_shell.h"

/**
 * _strchr - locates a character in a string
 * @str: the string
 * @c: the character
 * Return: a pointer to the memory area str
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * _strtok - splits a string into words. Repeat delimiters are ignored
 * @str: the string
 * @delimiters: the delimiter string
 * Return: a pointer to an array of strings, or NULL in failure
 */
char **_strtok(char *str, char *delimiters)
{
	int i, j, k, m, numWords = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delimiter(str[i], delimiters) &&
				(is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
			numWords++;
	}
	if (numWords == 0)
		return (NULL);
	result = malloc((1 + numWords) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (is_delimiter(str[i], delimiters))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], delimiters) && str[i + k])
			k++;
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result[j][m] = str[i++];
		result[j][m] = '\0';
	}
	result[j] = NULL;
	return (result);
}

/**
 * _strtok2 - splits a string into words
 * @str: the string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtok2(char *str, char delimiter)
{
	int i, j, k, m, numWords = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
			(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			numWords++;
	}
	if (numWords == 0)
		return (NULL);
	result = malloc((1 + numWords) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result[j][m] = str[i++];
		result[j][m] = '\0';
	}
	result[j] = NULL;
	return (result);
}

/**
 * is_delimiter - check if character is a delimeter
 * @c: char to check
 * @dlm: delimeter
 * Return: 1 if true 0 on failure
 */
int is_delimiter(char c, char *dlm)
{
	while (*dlm)
		if (*dlm++ == c)
			return (1);
	return (0);
}
