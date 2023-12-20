#include "rsaf.h"

/**
 * populate - generates possible prime numbers and adds them to a list
 * @optimus: array holding filedescriptors of shared memory
 */
void populate(lock_m optimus[])
{
	ulong g = 0, h = 0, i = 0;
	ulong spear = 0;

	fprintf(stdout, "Populating...\n");
	for (g = 0; g < ARRAY_SIZE; g++)
	{
		if (g)
			h = 0;
		else
		{
			optimus[0].primes[0] = 2;
			optimus[0].primes[1] = 3;
			h = 2;
		}

		for (i = 1; h < P_BLOCKS; h++, i++)
		{
			spear = 6 * (i + (g * (1000000 / 6)));
			optimus[g].primes[h] = spear - 1;
			++h;
			optimus[g].primes[h] = spear + 1;
		}

		if (msync(optimus[g].primes, MEM_SIZE, MS_ASYNC | MS_INVALIDATE))
		{
			perror("No Populate");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * print_int - converts a long long int to a string
 * @buffer: address to a buffer to store values
 * @num: the int to be converted
 *
 * Return: pointer to the string, NULL on failure
 */
void print_int(char **buffer, ulong num)
{
	ulong copy = num;
	int count = 0, i = 0;

	if (num == 0)
	{
		(*buffer)[0] = '0';
		i = 1;
	}
	else
	{
		while (copy)
		{
			copy >>= 1;
			count++;
		}

		i = count;
		while (count >= 0)
		{
			(*buffer)[count] = (num % 10) + '0';
			num /= 10;
			--count;
		}
	}

	for (; i < 16; i++)
		(*buffer)[i] = '\0';
}
