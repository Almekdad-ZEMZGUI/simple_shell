#include "s_shell.h"

/**
 * clearInfo - initializes info_t struct
 * @info: struct
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - initializes info_t struct
 * @info: struct
 * @argv: argument
 */
void setInfo(info_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = _strtok(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAliases(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct
 * @all: all fields
 *
 * Return : true on succeed
 */
void freeInfo(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuffer)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freeStringArray(info->environ);
			info->environ = NULL;
		freeStringArray((void **)info->cmdBuffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}


