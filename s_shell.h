#ifndef _S_SHELL_
#define _S_SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: string
 * @next: points to the next node
 */
typedef struct StringList
{
    int num;
    char *data;
    struct StringList *next;
} str_list_t;

/* str_func1 */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
int _putchar(char character);

/* str_func2 */
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(const char *str);
char *_strncat(char *dest, char *src, int n);
void _puts(char *str);


/* str_func3 */
char *_strchr(char *str, char c);
char **_strtok(char *str, char *delimiters);
char **_strtok2(char *str, char delimiter);
int is_delimiter(char c, char *dlm);

/* mem_func */
int freePointer(void **ptr);
char *memSet(char *memory, char byte, unsigned int size);
void freeStringArray(char **stringArray);
void *reallocateMemory(void *prevPtr, unsigned int oldSize, unsigned int newSize);

/* linked_lis */
str_list_t *addNode(str_list_t **head, const char *data, int num);
str_list_t *addNodeEnd(str_list_t **head, const char *data, int num);
size_t printStr(const str_list_t *h);
int deleteNodeAtIndex(str_list_t **head, unsigned int index);
void freeList(str_list_t **head_ptr);

#endif /* _S_SHELL_ */

