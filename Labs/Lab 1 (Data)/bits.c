/* 
 * CS:APP Data Lab 
 * 
 * Jonathan Chu
 * 004832220
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*Uses the fact that ~x == -1 if and only if x == 0 and that x | y == 0 if and only if x == 0 
and y == 0*/
  int a = ~x + 1;
  return ((x | a) >> 31) + 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/*Counts bits within every 2-bit pair, then every 4-bit group, and so on until the whole 32-bit integer
is accounted for. Implements a right shift along with the proper masks to count 1's.*/
  int mask11 = (0x55 << 8) + 0x55;
  int mask1 = mask11 + (mask11 << 16);
  int mask21 = (0x33 << 8) + 0x33;
  int mask2 = mask21 + (mask21 << 16);
  int mask31 = (0x0f << 8) + 0x0f;
  int mask3 = mask31 + (mask31 << 16);
  int mask4 = (0xff << 16) + 0xff;
  int mask5 = (0xff << 8) + 0xff;

  int a = (x & mask1) + ((x >> 1) & mask1);
  int b = (a & mask2) + ((a >> 2) & mask2);
  int c = (b & mask3) + ((b >> 4) & mask3);
  int d = (c & mask4) + ((c >> 8) & mask4);
  int e = (d & mask5) + ((d >> 16) & mask5);
  return e;
}

/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
/*Finds bits that are 0 in both x and y and inverts those bits to 
yield the same result as |*/
	return ~((~x) & (~y));
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
/*Simply masks the desired bits then left shifts, copies, and repeats. Does not left shift if
amount to shift by is greater than 32, as this is undefined.*/
  int inv = (1 << 31) >> (31 - n);
  int mask = (~inv) | (((!(n ^ 32)) << 31) >> 31);

  int n2 = (n * 2) & (((n / 16) - 1));
  int n4 = (n * 4) & (((n / 8) - 1)); 
  int n8 = (n * 8) & (((n / 4) - 1));
  int n16 = (n * 16) & (((n / 2) - 1)); 
  
  unsigned int lower = x & mask;
  unsigned int first = lower | (lower << n);
  unsigned int second = first | (first << (n2));
  unsigned int third = second | (second << (n4));
  unsigned int fourth = third | (third << (n8));
  unsigned int fifth = fourth | (fourth << (n16));
  return fifth;
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
/*Shifts left then shifts right so that only n bits aren't truncated. Then, the result after these
two shifts is compared to the original bit pattern to check whether it has the same value or a 
different value.*/
  int inverse = ~x;
  int a = x << (32 + ~n + 1);
  int b = a >> (32 + ~n + 1);
  return !~(inverse ^ b);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*Shifts  the desired byte to the rightmost position (of 8 bits), utilizing the 
  left shift to multiply n by 8, and masks the integer to return just those 8 bits*/
  int b = x >> (n << 3); 
  return b & 0xff;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*Simply takes a difference (by adding ~x + 1) and makes sure checks sign differences between x and y
to account for overflow*/
  int xsgn = !(x >> 31);
  int ysgn = !(y >> 31);
  int ls = (xsgn ^ ysgn) & ysgn; // means that x was negative and y was positive, meaning must be less than 
  int gr = (xsgn ^ ysgn) & xsgn; // means that y was negativand x was positive
  
  int same = !(x ^ y);

  int diff = y + ~x + 1;
  int b = diff >> 31;
  int sign = !!diff & !(b); 
  return ((!gr) & (ls | (!!sign))) | same;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/*Copies leading bit into every bit of the integer and utilizes '!' to check whether that leading
bit was 0 or 1. Accounts for the 0 case by taking advantage of the fact that 0 is the only number 
which after a '!' yields 1.*/
  int b = x >> 31;
  return !!x & !(b); 
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/*Performs an arithmetic shift and then turns all the bits into which the MSB was copied and turns 
them to zero, using a mask. The mask was created using INT_MIN (10000...0), arithmetically right 
shifting it to occupy more of the left bits, and finally inverting it using '~'.*/
  int min = 0x8 << 28;
  int inv = min >> (n) << 1;
  int mask = ~inv;
  return mask & (x >> n);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*The bit equivlaent to 0x8, 1000, shifted to the leftmost position 
  is equivalent to the minimum 2's complement integer.*/
  return 0x8 << 28;
}
