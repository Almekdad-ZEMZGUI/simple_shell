#include "s_shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure used to maintain constant function prototype
 *  Return: exits with exit status, or 0
 */
int exit_shell(info_t *info)
{
	int exit_code;

	if (info->arguments[1])
	{
		exit_code = safe_atoi(info->arguments[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_custom_err(info, "Illegal number: ");
			_eputs(info->arguments[1]);
			_eputchar('\n');
			return (1);
		}
		info->errNum = safe_atoi(info->arguments[1]);
		return (-2);
	}
	info->errNum = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory
 * @info: Structure used to maintain constant function prototype
 *  Return: 0
 */
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_result;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arguments[1])
	{
		dir = getEnvironmentVariable(info, "HOME=");
		if (!dir)
			chdir_result =
				chdir((dir = getEnvironmentVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (_strcmp(info->arguments[1], "-") == 0)
	{
		if (!getEnvironmentVariable(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getEnvironmentVariable(info, "OLDPWD=")), _putchar('\n');
		chdir_result =
			chdir((dir = getEnvironmentVariable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(info->arguments[1]);
	if (chdir_result == -1)
	{
		print_custom_err(info, "can't cd to ");
		_eputs(info->arguments[1]), _eputchar('\n');
	}
	else
	{
		setEnvironmentVariable(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
		setEnvironmentVariable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_help - displays help information
 * @info: Structure used to maintain constant function prototype
 *  Return: 0
 */
int show_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->arguments;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}

/**
 * display_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure used to maintain constant function prototype
 *  Return: 0
 */
int display_history(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * manage_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: 0
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	str_list_t *node = NULL;

	if (info->argumentCount == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->arguments[i]; i++)
	{
		p = _strchr(info->arguments[i], '=');
		if (p)
			assign_alias(info, info->arguments[i]);
		else
			display_alias(nodePrefix(info->alias, info->arguments[i], '='));
	}

	return (0);
}


