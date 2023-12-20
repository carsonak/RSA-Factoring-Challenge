#ifndef _RSAF_H_
#define _RSAF_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>

/*Every prime number above 3 can be repsented in the form (6n +/- 1)*/
#define P_BLOCKS (((1000000 / 6) * 2) + 1)
#define MEM_SIZE (sizeof(ulong) * P_BLOCKS)
#define B_PAGES (((MEM_SIZE / sysconf(_SC_PAGE_SIZE)) + 1) * sysconf(_SC_PAGE_SIZE))
#define ARRAY_SIZE (2)

/**
 * struct mem_lock_array - simple list with a mutex
 * @primes: a shared memory mapping.
 */
typedef struct mem_lock_array
{
	ulong *primes;
} lock_m;

char *infiX_mul(char *n1, char *n2);
char *infiX_add(char *n1, char *n2);
ssize_t _strlen(char *s);
size_t _strspn(char *s, char *accept);
size_t pad_char(char *str, char *ch);
void print_int(char **buffer, ulong num);
int make_mm(lock_m **optimus, int fd);
void populate(lock_m optimus[]);
void operate(lock_m optimus[], size_t arr_sz);
void clean_exit(lock_m optimus[], int status, int fd, char *file_name);

#endif /*_RSAF_H_*/
