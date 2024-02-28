#include "s_shell.h"

/**
 * copyEnvironToStringArray - returns the string array copy of our environment
 * @info: Struct
 * Return: 0
 */
char **copyEnvironToStringArray(info_t *info)
{
    if (!info->environ || info->environmentChanged)
    {
        info->environ = listToString(info->environment);
        info->environmentChanged = 0;
    }

    return (info->environ);
}

/**
 * removeEnvironmentVariable - Remove an environment variable
 * @info: Structure
 * @variable: the string environment variable property
 * Return: 1 on delete, 0 otherwise
 */
int removeEnvironmentVariable(info_t *info, char *variable)
{
    str_list_t *node = info->environment;
    size_t index = 0;
    char *p;

    if (!node || !variable)
        return (0);

    while (node)
    {
        p = _starts_with(node->str, variable);
        if (p && *p == '=')
        {
            info->environmentChanged = deleteNodeAtIndex(&(info->environment), index);
            index = 0;
            node = info->environment;
            continue;
        }
        node = node->next;
        index++;
    }
    return (info->environmentChanged);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure
 * @variable: the string environment variable property
 * @value: the string environment variable value
 *  Return: Always 0
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
    char *buffer = NULL;
    str_list_t *node;
    char *p;

    if (!variable || !value)
        return (0);

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);
    node = info->environment;
    while (node)
    {
        p = _starts_with(node->str, variable);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buffer;
            info->environmentChanged = 1;
            return (0);
        }
        node = node->next;
    }
    addNodeEnd(&(info->environment), buffer, 0);
    free(buffer);
    info->environmentChanged = 1;
    return (0);
}


