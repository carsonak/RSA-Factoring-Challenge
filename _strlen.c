#include "rsaf.h"

/**
 *_strlen - calculates length of a string
 *@s: the string
 *
 *Return: length of the string
 */
ssize_t _strlen(char *s)
{
	ssize_t cnt;

	for (cnt = 0; s[cnt]; cnt++)
		;

	return (cnt);
}
