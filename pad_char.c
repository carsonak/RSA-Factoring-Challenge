#include "rsaf.h"

/**
 * pad_char - calculates length of initial padding characters in a string
 * @str: the string to check
 * @ch: the character
 *
 * Return: number of padding characters
 */
size_t pad_char(char *str, char *ch)
{
	size_t zeros = 0, len = 0;

	if (str)
	{
		len = _strlen(str);
		zeros = _strspn(str, ch);
		if (len && (zeros == len))
			zeros--;
	}

	return (zeros);
}
