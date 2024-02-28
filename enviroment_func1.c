#include "s_shell.h"

/**
 * displayEnvironment - prints the current environment
 * @info: Structure
 * Return: 0
 */
int displayEnvironment(info_t *info)
{
    printStr(info->environment);
    return (0);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @info: Structure
 * @name: environment variable name
 *
 * Return: the value
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
    list_t *node = info->environment;
    char *p;

    while (node)
    {
        p = _starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
    if (info->argumentCount != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (setEnvironmentVariable(info, info->arguments[1], info->arguments[2]))
        return (0);
    return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @info: Structure
 *  Return: 0
 */
int unsetEnvironmentVariable(info_t *info)
{
    int i;

    if (info->argumentCount == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argumentCount; i++)
        removeEnvironmentVariable(info, info->arguments[i]);

    return (0);
}

/**
 * populateEnvironmentList - populates environment linked list
 * @info: Structure.
 * Return: 0
 */
int populateEnvironmentList(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);
    info->environment = node;
    return (0);
}

