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
#include <stdarg.h>
#include <signal.h> /*sigaction()*/
#include <sys/mman.h> /*mmap()*/
#include <sys/wait.h> /*waitpid()*/
#include <fcntl.h> /*manipulate file descriptors*/

/*There are atmost 78,498 primes from 0 to 1,000,000*/
#define NODE_SZ (78498 + 1)
/*Memory for primes in range of a million*/
#define NODES_MEM ((sizeof(uint8_t) * 10) * NODE_SZ)
/*Page memory for primes in the range of a million*/
#define PG_MEM (((NODES_MEM / sysconf(_SC_PAGE_SIZE)) + 1) * sysconf(_SC_PAGE_SIZE))

/*Upper limit in millions, max performance*/
#define ARRAY_BLOCKS (1)
/*One Million*/
#define A_MILI (1000000)

/*8 bit blocks used to represent numbers in the whole range*/
#define SV_BLOCKS (((A_MILI * ARRAY_BLOCKS) / 8) + 1)
/*Total bytes used by all the 8 bit blocks*/
#define SV_SIZE (SV_BLOCKS * sizeof(uint8_t))
/*Page memory for all the 8 bit blocks*/
#define SV_PG_MEM (((SV_SIZE / sysconf(_SC_PAGE_SIZE)) + 1) * sysconf(_SC_PAGE_SIZE))

/*Pointer to a mapped memmory for the sieve*/
extern uint8_t *sieve;
/*Pointer to a mapped memmory for the prime numbers*/
extern uint8_t *optimus;
/*Global to check for interrupts*/
extern volatile sig_atomic_t interrupted;

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

/**
 * struct number_list - linked list for numbers read from a file
 * @len: Length of the number
 * @number: string containing only numbers
 * @next: pointer to the next node
 */
typedef struct number_list
{
	size_t len;
	uint8_t number[512];
	struct number_list *next;
} num_lst;

int int_tostr(int64_t num, uint8_t **str); /*Helper Functions*/
char *stringscat(size_t items, ...);
char *str_concat(char *s1, char *s2);
num_lst *insert_node_here(num_lst **node, char *numstr, size_t numlen);
num_lst *insert_node_end(num_lst **head, char *numstr, size_t numlen);
void free_list(num_lst *head);

num_lst *read_file(char *file_name); /*Main Functions*/
int make_mm(char *shared_file);
int populate(int file_des, int g, int step);
int sieve_o_atkins(int64_t limit);
int operate(num_lst *head, int shared_fd);
uint8_t *factorise(uint8_t *num, uint8_t **big_fct, int shared_fd);
void graceful(int thesignal);
void clean_exit(int fd, char *shared_file, num_lst *head, int status);

#endif /*_RSAF_H_*/
