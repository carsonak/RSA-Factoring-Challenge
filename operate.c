#include "rsaf.h"

/**
 * operate - print out some data from mapped memory
 * @optimus: array of structs with the mapped memory
 */
void operate(lock_m optimus[])
{
	size_t g = 0, h = 0;

	sleep(1);
	fprintf(stdout, "Reading......\n");
	for (g = 0; g < 5; g++)
	{
		pthread_mutex_lock(&optimus[g].mutex);
		for (h = 0; h < 20; h++)
		{
			printf("%6ld ", optimus[g].primes[h]);
			if (!(h % 5))
				putchar('\n');
		}

		pthread_mutex_unlock(&optimus[g].mutex);
	}
}
