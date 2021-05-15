/*
 * @Author: Y.t
 * @Date: 2021-05-09 16:54:17
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-15 10:29:27
 * @Description: 
 */

#ifndef BIGINT_H
#define BIGINT_H
#include <stdio.h>


struct bigint_struct;

// Define bigint to be a pointer to a bigint_struct
typedef struct bigint_struct* bigint;

// There are there ways to create a bigint
bigint bigint_from_str(char *s);
bigint bigint_from_int(int i);
bigint bigint_from_ints(int ints[], int count);
bigint bigint_copy(bigint source);

/* Bigints can be converted to integers. If it won't fit in an
integer, the program exits */
int bigint_to_int(bigint b);
char *bigint_to_str(bigint b);
char *bigint_to_hexstr(bigint b);

// Memory management
bigint bigint_alloc(int chunks);
void bigint_free(bigint b);

//There are seven arithmetic operations
bigint bigint_add(bigint l, bigint r);
bigint bigint_sub(bigint l, bigint r);
bigint bigint_mul(bigint l, bigint r);
bigint bigint_div(bigint l, bigint r);
bigint bigint_negate(bigint b);
bigint bigint_asb(bigint b);
bigint bigint_sqrt(bigint b);
bigint bigint_abs(bigint b);

// Two shift operations (all bigints are signed, so there is
// no such thing as an unsigned shift right)
bigint bigint_shift_left(bigint l, int shamt);
bigint bigint_shift_right(bigint l, int shamt);

// There are seven comparision operations.
int bigint_is_zero(bigint b);
int bigint_le(bigint l, bigint r);
int bigint_lt(bigint l, bigint r);
int bigint_ge(bigint l, bigint r);
int bigint_gt(bigint l, bigint r);
int bigint_eq(bigint l, bigint r);
int bigint_ne(bigint l, bigint r);


/* Low_level comparision. bigint_cmp compares two bigints
   return -1 if l<r
   return 0  if l==r
   return 1  if l>r
*/
int bigint_cmp(bigint l, bigint r);

// Functions for binary input/output
void bigint_write_binary(FILE *f, bigint x);
bigint bigint_read_binary(FILE *f);


#endif
