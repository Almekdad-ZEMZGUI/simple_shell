#include "s_shell.h"

/**
 * isCmd - determines if a file is executable command
 * @info: the struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer
 */
char *dupChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findPath - finds this cmd in the PATH string
 * @info: the info struct
 * @spath: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd, NULL otherwise
 */
char *findPath(info_t *info, char *spath, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!spath)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (isCmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!spath[i] || spath[i] == ':')
		{
			path = dupChars(spath, current_position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isCmd(info, path))
				return (path);
			if (!spath[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

