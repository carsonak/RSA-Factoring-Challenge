#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: array of structs with the mapped memory
 * @arr_sz: size of the array
 */
void operate(lock_m optimus[], size_t arr_sz)
{
	size_t g = 0, h = 0;

	fprintf(stdout, "Reading......\n");
	for (g = 0; g < arr_sz; g++)
	{
		for (h = 0; h < 9; h++)
		{
			printf("%6ld ", optimus[g].primes[h]);
			if (!(h % 16) && h > 1)
				putchar('\n');
		}
		putchar('\n');
		putchar('\n');
	}
}
