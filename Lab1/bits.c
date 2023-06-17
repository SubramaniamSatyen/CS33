/* 
 * CS:APP Data Lab 
 * 
 * Satyen Subramaniam 005737472
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. 

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
       /*Realize that for Tmax, adding one is the same as negating (this is also true for -1). As such, we verify that 
       this holds true for x, and that x is not negative 1*/
       int plusOne, negOne;
       //Determine if input is edge case of -1
       negOne = !(x + 1);
       //Add 1 to x and take NOT of x (should be same value for both -1 and Tmax)
       plusOne = x+1;
       x = ~x;
       //If (x+1) and NOT x match AND it x != -1, then return 1, otherwise return 0
       return (!(plusOne ^ x)) & !negOne ;
}

/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /*Create the first byte and copy it into the other four bytes by using the left shift operator*/
  int byte, res;
  //Shifting and adding 0101 0101 byte
  byte = 0x55;
  res = byte;
  res <<= 8;
  res += byte;
  res <<= 8;
  res += byte;
  res <<= 8;
  res += byte;
  return res;
}
//2
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  /*Takes advantage of XOR. Essentially if two input ints are the same, their bits are identical, meaning their 
  XOR should be 0 (with no exclusive bits). We can't use AND or OR here since they would consider extra possibilites*/
  return !(x ^ y);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*We consider to n = 32 to be an edge case where the function is always true. For positive numbers, we take advantage 
  of the fact that they are solely encoded in the minimum number of bits. By left shifting, then right shifting, both times
  by the number of restricted bits (32 - n), we expect to get the same value of x, if it fits in n bits. For negative values,
  we realize that this observation should also hold true (although the leading bits will all be 1 instead of 0) */
  int isThTwo, test, neg;
  //Checking if n is 32
  isThTwo = !(n ^ 32);
  //Calculating 32 - n
  neg = ~n + 33;
  //Calculating the test value to compare to x. We expect these to be the same if x fits in n bits
  test = x << neg;
  test = test >> neg;
  //printf("\n x: %x (%d), n: %x (%d), -n: %x (%d),  Calculated: %x (%d)", x, x, n, n, neg, neg, test, test);
  //printf("\n inputLegal: %x, XOR: %x, is32: %x", (!(x^test)), (x ^ test), (notThTwo));
  return (!(x ^ test)) | isThTwo;
}
//3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*Takes advantage of the fact that 0 is false. Determines if x is false, then creates holder with either all 1s or 0s, which is
  used in the return statement*/
  int isTrue;
  //Determining if x is true (if it is not zero) by XOR method, and setting last bit to either 1 (true) or 0 (false)
  isTrue = !(!(x ^ 0x0));
  //Setting all bits in isTrue to value of last bit
  isTrue <<= 31;
  isTrue >>= 31;
  //printf("\n x: %x (%d), isTrue: %x (%d)", x, x, isTrue, isTrue);
  //printf("\n y: %x (%d), returnY: %x (%d)", y, y, (isTrue & y), (isTrue & y));
  //printf("\n z: %x (%d), returnZ: %x (%d)\n", z, z, (~isTrue & z), (~isTrue & z));
  //return y if isTrue is all 1s and z if isTrue is all 0s
  return (isTrue & y) | ((~isTrue) & z);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*First, we consider the case where x is positive and y is negative, and realize the output is always 1. 
  We then consider that if y is positive and x is negative, then the output should always be 0. We find these
  values by looking at the leading bit of x. We then consider the case where x and y have the same sign, and realize
  that x - y should always be positive if x > y */
  int xNeg, yNeg, diffSign, signGreat, diff, negY;
  //Shifting the leading bit of x and y to fill the entire bit
  xNeg = (x >> 31);
  yNeg = (y >> 31);
  //Determine if x and y match (all 1s means don't match, 0s means match)
  diffSign = (xNeg ^ yNeg);
  //If y was negative and the signs were different, then signGreat is set to 1s
  signGreat = (!(diffSign ^ yNeg)) & diffSign;
  //Calculating negative y (to calculate x - y)
  negY = ~y + 1;
  //Calculate x - y and fill diff with the first bit (to indicate sign)
  diff = x + negY;
  diff = (diff >> 31);

  // printf("\nsignsDiff: %x (%d)", diffSign, diffSign);
  // printf("\n-,+: %x (%d), +,-: %x (%d), sign: %x (%d)", signLess, signLess, signGreat, signGreat,diff, diff);
  // printf("\nSign Part: %x (%d)", (!signLess & diffSign), (!signLess & diffSign));
  // printf("\nValidation: %x (%d), NotSame: %x (%d), PosDiff: %x (%d), notEdge: %x (%d)", ((!(!(x ^ y))) &  ((!(diff ^ 0x0)) & (!((x << 1) ^ 0x0)))), ((!(!(x ^ y))) &  ((!(diff ^ 0x0)) & (!((x << 1) ^ 0x0)))), (!(!(x ^ y))), (!(!(x ^ y))), (!(diff ^ 0x0)), (!(diff ^ 0x0)), !((x << 1) ^ 0x0), !((x << 1) ^ 0x0));
  // printf("\nx: %x (%d), y: %x (%d), XOR: %x (%d), !!XOR: %d", x, x, y, y, (x ^ y), (x ^ y), (!(!(x ^ y))), (!(!(x ^ y))));

  //if the signs match return 1, otherwise, return whether the signs are the same AND x and y are different AND 
  //the difference has the same sign AND x is not the edge case of Tmin (which would always be false)
  return ((signGreat) + ((!(!(x ^ y))) & (!(diff ^ 0x0)) & !(!((x << 1) ^ 0x0)) & ~diffSign));
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  /*Take advantage of left shift ability to multiply by two as well as the relationship between addition and multiplication.
   We then intend to take advantage of the right shift ability to divide by a power of two to divide by 8. However, noting 
   that the right shift takes the floor of the division, we need to bump negative results by 7 so that they floor to the 
   next largest number (if there is some remainder)*/
  int five, negShift;
  //Calculating 5 * x
  five = ((x << 2) + x);
  //printf("\n x: %x (%d), 5 * x: %x (%d)", x, x, five, five);
  //If the number is negative (first bit is 1), store 7 in negShift
  negShift = ((x >> 31) & 7);
  return ((five + negShift) >> 3);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*Takes advantage of the fact zero does not have negative. First, note that if value is negative, we know it is true, so return 0
  by use of the & operator. If x is not negative, we consider if negative X is negative (has a leading 1). If it is never negative, then 
  we mask with 1 to return 1, otherwise we return 0*/
  int notNeg, negX, notMadeNeg;
  //Determine if x is a negative value from first bit. All 1s corresponds to not negative, all 0s corresponds to negative.
  notNeg = ~(x >> 31);
  //Determines if, after negating, x is negative (same method as above). Note that Tmin will be negative and made negative,
  //but redundancy doesn't matter.
  negX = (~x) + 1;
  notMadeNeg = ~(negX >> 31);
  //If neither calculation yielded a negative value, then we know that x is zero, and return true.
  return (notNeg & notMadeNeg) & 0x1;
}
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  /*We first assume x is positive, and realize that the encoding will be the same as x's encoding. Now, we consider the case
  of x being negative, understanding the encoding should be the encoding of the positive value of x with a leading bit of 1*/
  int xLead, negX, negBit;
  //Determine if x is positive (store 0 in xLead) or negative (store -1 in xLead)
  xLead = (x >> 31);
  //Calculate the opposite signed version of x. We will use this if x is negative
  negX = (~x) + 1;
  //Prepare the leading sign bit
  negBit = (0x1 << 31);
  negX += negBit;
  //If x was negative, return the encoding of positive x with the leading sign bit, otherwise return x.
  return (xLead & negX) | (~xLead & x);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*Takes advantage of the fact that power of two will only have a single 1 bit. We thus expect x-1 to be a series of 1s,
  following the 1 bit of x. By using this, we expect x + (x-1) and x ^ (x-1) to be the same. As such we can verify these values
  are equal with an XOR, and return 1 if they are the same. We treat 0 as an edge case and make sure x is not zero.*/
  int oneLess, diff, sum, notNeg;
  //Determine if x is negative (if it is, we know to return 0)
  notNeg = ~(x >> 31);
  //Calculate x-1
  oneLess = x + (~0x0);
  //Determine the XOR of x and x-1
  diff = x ^ oneLess;
  //Determine the sum of x and x-1
  sum = x + oneLess;
  //printf("\n x: %x (%d), x-1: %x (%d), x+x-1: %x (%d), XOR: %x (%d)", x, x, oneLess, oneLess, sum, sum, diff, diff);
  //printf("\n valid: %x (%d), notNeg: %x (%d)", (!(diff ^ sum)), (!(diff ^ sum)), notNeg, notNeg);
  //printf("\n res: %x (%d)", (!(diff ^ sum)) & notNeg);
  //If x is not negative, x is not zero (which I standardize with !), and the XOR and sum of x and x-1 are the same, return 1 
  return (!(diff ^ sum)) & notNeg & !(!(x));
}
