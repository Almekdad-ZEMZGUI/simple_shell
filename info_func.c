#include "s_shell.h"

/**
 * clearInfo - initializes info_t struct
 * @info: struct
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->arguments = NULL;
	info->path = NULL;
	info->argumentCount = 0;
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
		info->arguments = _strtok(info->arg, " \t");
		if (!info->arguments)
		{

			info->arguments = malloc(sizeof(char *) * 2);
			if (info->arguments)
			{
				info->arguments[0] = _strdup(info->arg);
				info->arguments[1] = NULL;
			}
		}
		for (i = 0; info->arguments && info->arguments[i]; i++)
			;
		info->argumentCount = i;

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
	freeStringArray(info->arguments);
	info->arguments = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuffer)
			free(info->arg);
		if (info->environment)
			freeList(&(info->environment));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freeStringArray(info->environ);
			info->environ = NULL;
		freePointer((void **)info->cmdBuffer);
		if (info->readFd > 2)
			close(info->readFd);
		_putchar(BUFFER_FLUSH);
	}
}


