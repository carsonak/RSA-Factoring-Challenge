#ifndef _INFIX_H_
#define _INFIX_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>

/*A dynamically allocated buffer to store the remainder of division*/
extern uint8_t *remain;

/**
 * struct operations - a structure of an operation and it's function
 * @sign: the operation
 * @f: a pointer to the corresponding function
 */
typedef struct operations
{
	char *sign;
	uint8_t *(*f)(uint8_t *n1, uint8_t *n2);

} op_func;

uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor);
uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2);
uint8_t *infiX_mul(uint8_t *n1, uint8_t *n2);
uint8_t *infiX_add(uint8_t *n1, uint8_t *n2);
size_t pad_char(char *str, char *ch);
size_t strtonul(char *num, size_t nelem);
void *memfill(void *mem, char b, size_t start, size_t nbytes);

#endif /*_INFIX_H_*/
