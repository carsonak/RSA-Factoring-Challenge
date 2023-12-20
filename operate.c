#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: array of structs with the mapped memory
 * @arr_sz: size of the array
 */
void operate(lock_m optimus[], size_t arr_sz)
{
	size_t g = 0, h = 0;

	//(void)arr_sz;
	for (g = 0; g < arr_sz; g++)
	{
		for (h = 0; h < P_BLOCKS; h++)
		{
			if (!((h + 1) % 17) && h > 1)
				putchar('\n');
			printf("%7ld ", optimus[g].primes[h]);
		}
		putchar('\n');
	}
}
