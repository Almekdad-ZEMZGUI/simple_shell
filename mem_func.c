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
void *reallocateMemory(void *prevPtr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!prevPtr)
		return (malloc(newSize));
	if (!newSize)
		return (free(prevPtr), NULL);
	if (newSize == oldSize)
		return (prevPtr);

	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)prevPtr)[oldSize];
	free(prevPtr);
	return (newPtr);
}

