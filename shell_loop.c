#include "s_shell.h"

/**
 * shellLoop - main shell loop
 * @info: the parameter of info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error to stdrr
 */
int shellLoop(info_t *info, char **argv)
{
	ssize_t bytesRead = 0;
	int builtinReturn = 0;

	while (bytesRead != -1 && builtinReturn != -2)
	{
		clearInfo(info);
		if (check_interactive_mode(info))
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		bytesRead = getInput(info);
		if (bytesRead != -1)
		{
			setInfo(info, argv);
			builtinReturn = findBuiltin(info);
			if (builtinReturn == -1)
				findCommand(info);
		}
		else if (check_interactive_mode(info))
			_putchar('\n');
		freeInfo(info, 0);
	}
	writeHistory(info);
	freeInfo(info, 1);
	if (!check_interactive_mode(info) && info->status)
		exit(info->status);
	if (builtinReturn == -2)
	{
		if (info->errNum == -1)
			exit(info->status);
		exit(info->errNum);
	}
	return (builtinReturn);
}

/**
 * findBuiltin - finds a builtin command
 * @info: the parameter of info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
	int i, builtinReturn = -1;
	_builtin_tbl builtinTable[] = {
		{"exit", exit_shell},
		{"env", displayEnvironment},
		{"help", show_help},
		{"history", display_history},
		{"setenv", _mysetenv},
		{"unsetenv", unsetEnvironmentVariable},
		{"cd", change_directory},
		{"alias", manage_alias},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].type; i++)
		if (_strcmp(info->arguments[0], builtinTable[i].type) == 0)
		{
			info->lineCount++;
			builtinReturn = builtinTable[i].func(info);
			break;
		}
	return (builtinReturn);
}

/**
 * findCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_t *info)
{
	char *commandPath = NULL;
	int i, countArgs;

	info->path = info->arguments[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (i = 0, countArgs = 0; info->arg[i]; i++)
		if (!is_character_delimiter(info->arg[i], " \t\n"))
			countArgs++;
	if (!countArgs)
		return;

	commandPath = findPath(info, getEnvironmentVariable(info, "PATH="), info->arguments[0]);
	if (commandPath)
	{
		info->path = commandPath;
		forkCommand(info);
	}
	else
	{
		if ((check_interactive_mode(info) || getEnvironmentVariable(info, "PATH=") || info->arguments[0][0] == '/') && isCmd(info, info->arguments[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_custom_err(info, "not found\n");
		}
	}
}

/**
 * forkCommand - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(info_t *info)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info->path, info->arguments, copyEnvironToStringArray(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_custom_err(info, "Permission denied\n");
		}
	}
}


