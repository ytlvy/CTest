/*
 * @Author: Y.t
 * @Date: 2021-05-10 11:32:13
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-10 11:52:50
 * @Description: 
 */
// 128-bit / 64-bit unsigned divide

#include <stdio.h>
#include <stdint.h>

int main(void) {
  // numerator
  uint64_t a_lo = 100;
  uint64_t a_hi = 100;

  // denominator
  uint64_t b = 5;

  // quotient
  uint64_t q = a_lo << 1;
  uint64_t q_hi = 0;

  // remainder
  uint64_t rem = a_hi;

  uint64_t carry = a_lo >> 63;
  uint64_t temp_carry = 0;
  int i;

  for(i = 0; i < 64; i++)
  {
    temp_carry = rem >> 63;
    rem <<= 1;
    rem |= carry;
    carry = temp_carry;

    if(carry == 0)
    {
      if(rem >= b)
      {
        carry = 1;
      }
      else
      {
        temp_carry = q >> 63;
        q <<= 1;
        q |= carry;
        carry = temp_carry;
        continue;
      }
    }

    rem -= b;
    rem -= (1 - carry);
    carry = 1;
    temp_carry = q >> 63;
    q <<= 1;
    q |= carry;
    carry = temp_carry;
  }

  printf("quotient = %llx\n", (long long unsigned int)q);
  printf("remainder = %llu\n", (long long unsigned int)rem);
  return 0;
}
