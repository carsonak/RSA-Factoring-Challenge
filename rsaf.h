#ifndef _RSAF_H_
#define _RSAF_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>	/*sqrt()*/
#include <stdint.h> /*strict data tyoe sizes*/
#include <sys/types.h>
#include <sys/mman.h> /*mmap()*/
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/*There are atmost 78,498 primes from 1 to 1,000,000*/
#define NODE_SZ (78498 + 1)

/*Memory for primes in range of a million*/
#define NODES_MEM (sizeof(ssize_t) * NODE_SZ)

/*Number of pages for primes in range of a million*/
#define PG_COUNT ((NODES_MEM / sysconf(_SC_PAGE_SIZE)) + 1)

/*Page memory for primes in range of a million*/
#define PG_MEM (PG_COUNT * sysconf(_SC_PAGE_SIZE))

/*Upper limit in millions*/
#define ARRAY_BLOCKS (3)

/*One Million*/
#define A_MILI (1000000)

/**
 * struct flock_primes_file - a sstruct for setting advisory locks
 * @l_type: Type of lock: F_RDLCK, F_WRLCK, F_UNLCK
 * @l_whence: How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END
 * @l_start: Starting offset for lock
 * @l_len: Number of bytes to lock
 * @l_pid: PID of process blocking our lock (set by F_GETLK and F_OFD_GETLK)
 */
typedef struct flock_primes_file
{
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
} pf_lock;

char *infiX_mul(char *n1, char *n2);
char *infiX_add(char *n1, char *n2);
ssize_t _strlen(char *s);
size_t _strspn(char *s, char *accept);
size_t pad_char(char *str, char *ch);
int make_mm(size_t **optimus, int fd);
int populate(uint64_t *optimus, u_int8_t *sieve, int file_des, int g, int step);
u_int8_t *sieve_o_atkins(u_int64_t range);
void operate(size_t *optimus, int file_des);
void clean_exit(size_t *optimus, int status, int fd, char *file_name);

#endif /*_RSAF_H_*/
