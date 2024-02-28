#include "s_shell.h"

/**
 * getHistoryFile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getHistoryFile(info_t *info)
{
	char *buffer, *dir;

	dir = getEnvironmentVariable(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * writeHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	str_list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoryList(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buffer, int linecount)
{
	str_list_t *node = NULL;

	if (info->history)
		node = info->history;
	addNodeEnd(&node, buffer, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
	str_list_t *node = info->history;
	int index = 0;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}
	return (info->histcount = index);
}

