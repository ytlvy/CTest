/*
 * @Author: Y.t
 * @Date: 2021-05-09 17:07:19
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-15 10:31:29
 * @Description: 
 */

#include "bigint.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>

/*
 A big integer is an array of "chunks" of bits. The following
 section defines the chunk, and defines a bigchunk to have twice
 as many bits as a chunk. It also defines a mask that can
 be used to select bit out of a bigchunk. When compiling this 
 code , you can define the chunk size by defining EIGHT_BIT,
 SIXTEEN_BIT, or SIXTYFOR_BIT. If none of those are defined, 
 then the chunk size is THIRTYTWO_BIT
*/

#define SIXTYFOUR_BIT 1

#ifdef EIGHT_BIT
    typedef uint8_t chunk;
    typedef int8_t schunk;
    typedef uint16_t bigchunk;
    #define CHUNKMASK 0xFFU
#else 
    #ifdef SIXTEEN_BIT
        typedef uint16_t chunk;
        typedef int16_t schunk;
        typedef uint32_t bigchunk;
        #define CHUNKMASK 0xFFFFU
    #else
        #ifdef SIXTYFOUR_BIT
            typedef uint64_t chunk;
            typedef int64_t schunk;
            typedef __uint128_t bigchunk;
            #define CHUNKMASK 0xFFFFFFFFFFFFFFFFULL
        #else
            typedef uint32_t chunk;
            typedef int32_t schunk;
            typedef uint64_t bigchunk;
            #define CHUNKMASK 0xFFFFFFFFU
        #endif
    #endif
#endif

//Macros
#define BITSPERCHUNK ((sizeof(chunk)<<3))
#define MSBFORCHCUNK ((bigchunk)1<<(BITSPERCHUNK -1))
#define MAX(a,b) ((a<b)?b:a)

//A bigint is an array of chunks of bits
struct bigint_struct {
    chunk *blks;      //pointer to array of bit chunks
    int size;         //number of chunks int the array
};

//Private function prototypes
static bigint bigint_adc(bigint l, bigint r, chunk carry);
static bigint bigint_shift_left_chunk(bigint l, int chunks);
static bigint bigint_shift_right_chunk(bigint l, int chunks);
static bigint bigint_trim(bigint b);
static bigint bigint_mul_uint(bigint l, chunk r);
static bigint bigint_extend(bigint b, int nchunks);
static unsigned bigint_smallmod(bigint b, chunk num);

//############################################
/* Initialization, conversion, and copy functions*/
//############################################

//convert string to bigint
bigint bigint_from_str(char *s) {
    bigint d;
    bigint power;
    bigint ten;
    bigint tmp;
    bigint currprod;

    int i, negative =0;
    d = bigint_from_int(0);
    ten = bigint_from_int(10);
    power = bigint_from_int(1);

    if(*s == '-') {
        negative = 1;
        s++;
    }

    for ( i = strlen(s)-1; i >= 0; i--) {
        if(!isdigit(s[i])) {
            fprintf(stderr, "Cannot convert string to bigint\n");
        }
        tmp = bigint_from_int(s[i] - '0');
        currprod = bigint_mul(tmp, power);
        bigint_free(tmp);

        tmp = bigint_adc(currprod, d ,0);
        bigint_free(d);
        d = tmp;
        bigint_free(currprod);
        if(i > 0) {
            tmp = bigint_mul(power, ten);
            bigint_free(power);
            power = tmp;
        }
    }

    if(negative) {
        tmp = bigint_negate(d);
        bigint_free(d);
        d = tmp;
    }

    bigint_free(ten);
    bigint_free(power);

    return d;
}

bigint bigint_from_ints(int ints[], int count) {
    bigint tmp = bigint_alloc(count);
    for(int i = 0; i<count; i++) {
        tmp->blks[i] = ints[i];
    }
    return tmp;
}

bigint bigint_from_int(int val) {
    bigint d, tmp;
    int i;
    int nchunks = sizeof(int) / sizeof(chunk);
    if(nchunks < 1) {
        nchunks++;
    }
    d = bigint_alloc(nchunks);
    for (i = 0; i < d->size; i++) {
        d->blks[i] = (val >> (i*BITSPERCHUNK)) & CHUNKMASK;
    }
    tmp = bigint_trim(d);
    bigint_free(d);
    return tmp;
}

bigint bigint_copy(bigint source) {
    bigint r;
    r = bigint_alloc(source->size);
    memcpy(r->blks, source->blks, r->size*sizeof(chunk));
    return r;
}

int bigint_to_int(bigint b) {
    int i, negative=0, result=0;
    bigint tmp1, tmp2;
    tmp1 = bigint_trim(b); //make a trimmed copy
    if(tmp1->size*sizeof(chunk) > sizeof(int)) {
        fprintf(stderr, "Cannot convert bigint to int %ld bytes \n",
        (long)tmp1->size*sizeof(chunk));
        exit(1);
    }

    //check sign and negative 
    if(tmp1->blks[tmp1->size-1] & MSBFORCHCUNK) {
        negative = 1;
        tmp2 = bigint_negate(tmp1);
        bigint_free(tmp1);
        tmp1 = tmp2;
    }

    for (i = tmp1->size-1; i>=0; i--) {
        result |= (tmp1->blks[i]<<(i*BITSPERCHUNK));
    }
    bigint_free(tmp1);
    if(negative) {
        result = - result;
    }
    return result;
}

char *bigint_to_str(bigint b) {
    int negative = 0;
    unsigned remainder;
    char *s, *r;
    bigint tmp, tmp2;

    //rough estimate of the number of characters needed
    int chars = log10(pow(2.0, (b->size * BITSPERCHUNK))) + 3;
    int i = chars - 1;
    if( (s = (char *)malloc(1 + chars * sizeof(char))) == NULL) {
        perror("bigint_str");
        exit(1);
    }

    s[i] = 0; //set last character to ascii null
    tmp = bigint_copy(b);
    if(b->blks[tmp->size-1] & MSBFORCHCUNK) {
        negative = 1;
        tmp2 = bigint_negate(tmp);
        bigint_free(tmp);
        tmp = tmp2;
    }

    if(bigint_is_zero(tmp)) {
        s[--i] = '0';
    } else {
        do {
            remainder = bigint_smallmod(tmp, 10);
            s[--i] = remainder + '0';
        }while (!bigint_is_zero(tmp));
        if(negative) {
            s[--i] = '-';
        }
    }

    r = strdup(s + i);
    bigint_free(tmp);
    free(s);
    return r;
}

char *bigint_to_hexstr(bigint b) {
    int negative = 0;
    unsigned remainder;
    char *s, *r;
    bigint tmp, tmp2;

    //rough estimate of the number of characters needed
    int chars = log10(pow(2.0, (b->size * BITSPERCHUNK))) + 3;
    int i = chars - 1;
    if( (s = (char *)malloc(1 + chars * sizeof(char))) == NULL) {
        perror("bigint_str");
        exit(1);
    }

    s[i] = 0; //set last character to ascii null
    tmp = bigint_copy(b);
    if(b->blks[tmp->size-1] & MSBFORCHCUNK) {
        negative = 1;
        tmp2 = bigint_negate(tmp);
        bigint_free(tmp);
        tmp = tmp2;
    }

    if(bigint_is_zero(tmp)) {
        s[--i] = '0';
    } else {
        do {
            remainder = bigint_smallmod(tmp, 16);
            if(remainder < 10){
                s[--i] = remainder + '0';
            }
            else {
                s[--i] = remainder-10 + 'A';
            }
        }while (!bigint_is_zero(tmp));
        if(negative) {
            s[--i] = '-';
        }
    }

    r = strdup(s + i);
    bigint_free(tmp);
    free(s);
    return r;
}

void bigint_free(bigint b) {
    if(b == NULL) {
        return;
    }

    if(b->blks != NULL) {
        free(b->blks);
    }

    free(b);
}

static bigint bigint_adc(bigint l, bigint r, chunk carry) {
    bigint sum, tmpl, tmpr;
    int i, nchunks;
    bigchunk tmpsum;

    nchunks = MAX(l->size, r->size) + 1;
    tmpl = bigint_extend(l, nchunks);
    tmpr = bigint_extend(r, nchunks);
    sum = bigint_alloc(nchunks);

    for(i = 0; i< nchunks; i++) {
        tmpsum = (bigchunk) tmpl->blks[i] + (bigchunk)tmpr->blks[i] 
            + (bigchunk)carry;
        sum->blks[i] = tmpsum & CHUNKMASK;
        carry = (tmpsum >> BITSPERCHUNK) & CHUNKMASK;
    }

    bigint_free(tmpl);
    bigint_free(tmpr);
    tmpl = bigint_trim(sum);
    bigint_free(sum);
    return tmpl;
}

bigint bigint_add(bigint l, bigint r) {
    return bigint_adc(l, r, 0);
}

bigint bigint_complement(bigint b) {
    bigint r = bigint_copy(b);
    for (int i=0; i<r->size; i++) {
        r->blks[i] ^= CHUNKMASK;
    }
    return r;
}

bigint bigint_sub(bigint l, bigint r) {
    bigint tmp1, tmp2;
    tmp1 = bigint_complement(r);
    tmp2 = bigint_adc(l, tmp1, 1);
    bigint_free(tmp1);
    return tmp2;
}

static bigint bigint_mul_uint(bigint l, chunk r) {
    int i, negative = 0;
    bigchunk tmpchunk;
    bigint sum = bigint_from_int(0);
    bigint tmp1, tmp2;

    if(l->blks[l->size-1] & MSBFORCHCUNK) {
        negative ^= 1;
        l = bigint_negate(l);
    }

    for(i = 0; i<l->size; i++) {
        tmpchunk = (bigchunk)l->blks[i] * r;
        tmp1 = bigint_alloc(3);
        tmp1->blks[0] = tmpchunk & CHUNKMASK;
        tmp1->blks[1] = (tmpchunk>>BITSPERCHUNK) & CHUNKMASK;
        tmp1->blks[2] = 0;

        tmp2 = bigint_shift_left_chunk(tmp1, i);
        bigint_free(tmp1);
        tmp1 = bigint_adc(sum, tmp2, 0);
        bigint_free(sum);
        bigint_free(tmp2);
        sum = tmp1;
    }

    if(negative) {
        tmp1 = sum;
        sum = bigint_negate(sum);
        bigint_free(tmp1);
        bigint_free(l);
    }
    return sum;
}

bigint bigint_mul(bigint l, bigint r) {
    int i, negative = 0;
    bigint sum = bigint_from_int(0);
    bigint tmp1, tmp2;

    if(r->blks[r->size-1] & MSBFORCHCUNK) {
        negative = 1;
        r = bigint_negate(r);
    }

    for (i = 0; i < r->size; i++) {
        tmp1 = bigint_mul_uint(l, r->blks[i]);
        tmp2 = bigint_shift_left_chunk(tmp1, i);
        bigint_free(tmp1);
        tmp1 = sum;
        sum = bigint_adc(sum, tmp2, 0);
        bigint_free(tmp1);
        bigint_free(tmp2);
    }

    if(negative) {
        tmp1 = sum;
        sum = bigint_negate(sum);
        bigint_free(tmp1);
        bigint_free(r);
    }
    
    return sum;
}

bigint bigint_div(bigint l, bigint r) {
    bigint lt = bigint_trim(l);
    bigint rt = bigint_trim(r);
    bigint tmp;
    int shift, chunkshift, negative=0;
    if(lt->size < rt->size) {
        bigint q = bigint_from_int(0);
        bigint_free(lt);
        bigint_free(rt);
        return q;
    }

    if(r->blks[r->size-1] & MSBFORCHCUNK) {
        negative = 1;
        tmp = rt;
        rt = bigint_negate(rt);
        bigint_free(tmp);
    }

    if(l->blks[l->size-1] & MSBFORCHCUNK) {
        negative = 1;
        tmp = lt;
        lt = bigint_negate(lt);
        bigint_free(tmp);
    }

    //do shift by chunks
    chunkshift = lt->size - rt->size;
    if(chunkshift > 0) {
        tmp = rt;
        rt = bigint_shift_left_chunk(rt, chunkshift);
        bigint_free(tmp);
    }

    //do remaining shift bit by bit
    shift = 0;
    while((shift<(BITSPERCHUNK-1)) && bigint_lt(rt, lt)) {
        shift++;
        tmp = rt;
        rt = bigint_shift_left(rt, 1);
        bigint_free(tmp);
    }

    //total shift count ;; see as arm64 version
    shift += (chunkshift * BITSPERCHUNK);
    
    //loop to shift right and subtrack
    bigint q = bigint_from_int(0);
    while(shift>=0) {
        tmp = q;
        // assert(q->blks != NULL);
        q = bigint_shift_left(q, 1);
        bigint_free(tmp);
        
        if(bigint_le(rt, lt)) {
            tmp = lt;
            lt = bigint_sub(lt, rt);
            bigint_free(tmp);

            //change lsb from zero to one
            q->blks[0] |= 1;
        }
        tmp = rt;
        rt = bigint_shift_right(rt, 1);
        bigint_free(tmp);
        shift--;
    }

    if(negative) {
        tmp = bigint_negate(q);
        bigint_free(q);
        q = tmp;
    }

    bigint_free(rt);
    bigint_free(lt);
    return q;
}

#ifndef USE_ASM
bigint bigint_negate(bigint b) {
    bigint r = bigint_complement(b);
    bigint tmp1 = bigint_from_int(0);
    bigint tmp2 = bigint_adc(r, tmp1, 1);
    bigint_free(tmp1);
    bigint_free(r);
    return tmp2;
}
#endif

bigint bigint_abs(bigint b) {
    if(b->blks[b->size-1] & MSBFORCHCUNK) {
        return bigint_negate(b);
    }
    return bigint_copy(b);
}

bigint bigint_sqrt(bigint b) {
    bigint r = bigint_from_int(0), zero = bigint_from_int(0);
    bigint num = bigint_copy(b), tmp, resplusbit, bit;
    
    if(b->blks[b->size-1] & MSBFORCHCUNK) {
        fprintf(stderr, "Cannot compute square root of negaive num");
        exit(1);
    }

    //init bit to the largest power of 4 
    bit = bigint_alloc(b->size);
    bit->blks[bit->size-1]  = (bigchunk) 1<<(BITSPERCHUNK-2);
    for (int i = 0; i < bit->size-1; i++)
    {
        bit->blks[i] = 0;
    }

    while (bit->blks[bit->size-1] > b->blks[b->size-1])
    {
        bit->blks[bit->size-1] >>= 2;
    }
    
    if(bit->blks[bit->size-1] == 0) {
        bit->blks[bit->size-1] = ((bigchunk) 1<<(BITSPERCHUNK-2));
    }

    while (bigint_gt(bit, zero))
    {
        resplusbit = bigint_add(r, bit);
        if(bigint_ge(num, resplusbit)) {
            tmp = num;
            num = bigint_sub(num, resplusbit);
            bigint_free(tmp);

            tmp = bigint_shift_right(r, 1);
            bigint_free(r);
            r = bigint_add(tmp, bit);
            bigint_free(tmp);
        }
        else {
            tmp = r;
            r = bigint_shift_right(r, 1);
            bigint_free(tmp);
        }

        bigint_free(resplusbit);
        tmp = bit;
        bit = bigint_shift_right(bit, 2);
        bigint_free(tmp);
    }
    bigint_free(zero);
    bigint_free(num);
    bigint_free(bit);
    return r;
}

static bigint bigint_shift_left_chunk(bigint l, int chunks) {
    bigint tmp = bigint_alloc(l->size + chunks);
    for(int i = -chunks; i<l->size+chunks; i++) {
        if(i<0) {
            tmp->blks[i+chunks] = 0;
        }
        else {
            tmp->blks[i+chunks] = l->blks[i];
        }
    }
    return tmp;
}

#warning maybe error
static bigint bigint_shift_right_chunk(bigint l, int chunks) {
    bigint tmp = bigint_alloc(l->size - chunks);
    for (int i = 0; i < tmp->size; i++)
    {
        tmp->blks[i] = l->blks[i+chunks];
    }
    
    return tmp;
}

bigint bigint_shift_left(bigint l, int shamt) {
    bigint tmp;
    l = bigint_extend(l, l->size+1);
    int extra = shamt % BITSPERCHUNK;
    shamt = shamt / BITSPERCHUNK;
    if(shamt) {
        tmp =l;
        l = bigint_shift_left_chunk(l, shamt);
        bigint_free(tmp);
    }
    if(extra){
        for (int i = l->size-1; i > 0; i--)
        {
            l->blks[i] = (l->blks[i] << extra) | 
              (l->blks[i-1]>>(BITSPERCHUNK-extra));
        }
        l->blks[0] = (l->blks[0] << extra);
    }
    tmp = bigint_trim(l);
    bigint_free(l);
    return tmp;
}

bigint bigint_shift_right(bigint l, int shamt) {
    bigint tmp;
    schunk tmpc;
    int extra = shamt % BITSPERCHUNK;
    shamt = shamt / BITSPERCHUNK;
    l = bigint_shift_right_chunk(l, shamt);
    if(extra) {
        for(int i = 0; i<l->size-1;i++) {
            l->blks[i] = (l->blks[i]>>extra) | 
             (l->blks[i+1] << (BITSPERCHUNK-extra));
        }

        // do signed shift of top
        tmpc = l->blks[l->size - 1];
        tmpc >>= extra;
        l->blks[l->size - 1] = tmpc;
    }

    tmp = bigint_trim(l);
    bigint_free(l);
    return tmp;
}


//###################### test and compare
inline int bigint_is_zero(bigint b){
    for(int i=0; i<b->size; i++) {
        if(b->blks[i]) {
            return 0;
        }
    }
    return 1;
}

inline int bigint_le(bigint l, bigint r) {
    return bigint_cmp(l, r) < 1;
}

inline int bigint_lt(bigint l, bigint r) {
    return bigint_cmp(l, r) == -1;
}

inline int bigint_ge(bigint l, bigint r) {
    return bigint_cmp(l, r) > -1;
}

inline int bigint_gt(bigint l, bigint r) {
    return bigint_cmp(l ,r) == 1;
}

inline int bigint_eq(bigint l, bigint r) {
    return (bigint_cmp(l, r) == 0) ? 1 : 0;
}

inline int bigint_ne(bigint l, bigint r) {
    return abs(bigint_cmp(l, r));
}

int bigint_cmp(bigint l, bigint r) {
    bigint d = bigint_sub(l, r);
    int cmp = 1;
    if( (d->size == 0) || (d->size == 1 && d->blks[0] == 0)) {
        cmp = 0;
    }
    else if(d->blks[d->size-1] & MSBFORCHCUNK) {
        cmp = -1;
    }

    bigint_free(d);
    return cmp;
}

//#################binary input/output

void bigint_write_binary(FILE *f, bigint x) {
    if(fwrite(&(x->size), sizeof(x->size), 1, f) != 1) {
        perror("Write failed");
        exit(4);
    }

    if(fwrite(x->blks, sizeof(chunk), x->size, f) != x->size) {
        perror("Write failed");
        exit(4);
    }
}

bigint bigint_read_binary(FILE *f) {
    bigint r = (bigint)malloc(sizeof(struct bigint_struct));
    if(r == NULL) {
        perror("bigint_read_binary");
        exit(1);
    }

    if(fread(&(r->size), sizeof(r->size), 1, f) != 1) {
        free(r);    
        return NULL;
    }

    r->blks = (chunk *)malloc(r->size*sizeof(chunk));
    if(r->blks == NULL) {
        perror("bigint_read_binary");
        exit(2);
    }

    if(fread(r->blks, sizeof(chunk), r->size, f) != r->size) {
        perror("bigint_read_binary");
        exit(4);
    }

    return r;
}

bigint bigint_alloc(int chunks) {
    bigint r = (bigint)malloc(sizeof(struct bigint_struct));
    if(r == NULL) {
        perror("bigint malloc error");
        exit(1);
    }

    r->size = chunks;
    r->blks = (chunk *)malloc(chunks * sizeof(chunk));
    if(r->blks == NULL) {
        perror("bigint_alloc");
        exit(1);
    }
    return r;
}

static bigint bigint_trim(bigint b) {
    bigint d;
    int i = b->size-1;
    if(i > 0) {
        if(b->blks[i] == 0) {
            do {
                i--;
            }while(i > 0 && b->blks[i] == 0);
            if(b->blks[i] & MSBFORCHCUNK) {
                i++;
            }
        }
        else if(b->blks[i] == CHUNKMASK) {
            do {
                i --;
            }while(i>0 && b->blks[i] == CHUNKMASK);
            if(!(b->blks[i] & MSBFORCHCUNK)) {
                i++;
            }
        }   
    }
    i++;
    if(i < b->size) {
        d = bigint_alloc(i);
        memcpy(d->blks, b->blks, d->size*sizeof(chunk));
    }
    else {
        d = bigint_copy(b);
    }
    return d;
}

//smallmod divides a bigint by a small number
//and returns them modulus. b changes as a SIDE-effect
//this is used by the to_str funciton
static unsigned bigint_smallmod(bigint b, chunk num) {
    bigchunk tmp;
    int i;
    if(num >= MSBFORCHCUNK) {
        fprintf(stderr, "bigint_smallmod: divisor out of range");
        exit(1);
    }

    tmp = b->blks[b->size-1];
    for(i=b->size-1; i>0; i--) {//从高到低 依次做除法
        b->blks[i] = tmp/num;
        tmp = (tmp%num) << BITSPERCHUNK | b->blks[i-1];
    }

    b->blks[0] = tmp/num;
    tmp = tmp % num;
    return tmp;
}

static bigint bigint_extend(bigint b, int nchunks) {
    bigint tmp;
    int i, negative;
    negative = 0;
    if(b->blks[b->size-1] & MSBFORCHCUNK) {
        negative = 1;
    }

    tmp = bigint_alloc(nchunks);
    for(i=0; i<nchunks;i++) {
        if(i < b->size) {
            tmp->blks[i] = b->blks[i];
        }
        else if(negative) {
            tmp->blks[i] = CHUNKMASK;
        }
        else {
            tmp->blks[i] = 0;
        }
    }

    return tmp;
}














