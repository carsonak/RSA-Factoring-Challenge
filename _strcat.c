#include "rsaf.h"

/**
 *_strcat - appends a string to another string.
 *@dest: string to be extended.
 *@src: string to append.
 *
 * Return: pointer to final string.
 */

char *_strcat(char *dest, char *src)
{
	size_t i = 0, j = 0;

	while (dest[i] != '\0')
		i++;

	while (j <= strlen(src))
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	return (dest);
}
