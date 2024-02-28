#include "s_shell.h"

/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: arguments vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	_info_t info[] = { INFO_ZERO };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populateEnvironmentList(info);
	readHistory(info);
	shellLoop(info, av);
	return (EXIT_SUCCESS);
}

