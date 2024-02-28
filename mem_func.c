#include "s_shell.h"

/**
 * freePointer - frees a pointer
 * @ptr: address of the pointer to be free
 *
 * Return: 1 on freed, otherwise 0.
 */
int freePointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * memSet - fills memory with a constant byte
 * @memory: the pointer to the memory area
 * @byte: the byte to fill *memory with
 * @size: the amount of bytes to be filled
 * Return: pointer to the memory area memory
 */
char *memSet(char *memory, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memory[i] = byte;
	return (memory);
}

/**
 * freeStringArray - frees array of strings
 * @stringArray: string of strings
 */
void freeStringArray(char **stringArray)
{
	char **temp = stringArray;

	if (!stringArray)
		return;
	while (*stringArray)
		free(*stringArray++);
	free(temp);
}

/**
 * reallocateMemory - reallocates a block of memory
 * @prevPtr: pointer to previous malloc'ated block
 * @oldSize: byte size of the previous block
 * @newSize: byte size of the new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *prePtr, unsigned int os, unsigned int ns)
{
	char *newPtr;

	if (!prePtr)
		return (malloc(ns));
	if (!ns)
		return (free(prePtr), NULL);
	if (ns == os)
		return (prePtr);

	newPtr = malloc(ns);
	if (!newPtr)
		return (NULL);

	os = os < ns ? os : ns;
	while (os--)
		newPtr[os] = ((char *)prePtr)[os];
	free(prePtr);
	return (newPtr);
}

