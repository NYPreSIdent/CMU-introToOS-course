/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /* xor: if the correspond bits are not same, the
     * out put would be 1, and vice versa. 
     * or is combined with ~(~a & (~b)), and we can write nand
     * to determind wether the ones appear simultinously. */
    int negatedX = ~x;
    int negatedY = ~y;
    return ~(negatedX & negatedY) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    int baseValue = 0x80;
    return baseValue << 24;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    int TmaxValue = ~(0x80 << 24);
    return !(TmaxValue ^ x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /* due to the property of binary number, we konw if the least signific
     * number is 0, we can get a even number, if it's 1, we can get the odd
     * number. So the first step we do is check the least significant number 
     * of each four bits group from left to right. */
    int mask = ((0x11 << 8 + 0x11) << 8 + 0x11) << 8 + 0x11;
    return !(mask ^ x); 
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}

//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // We know x is 
    int delta1 = 0x29 + (~x) + 1;
    int delta2 = x + (~0x40 + 1);
    return ((delta1 >> 31) & (delta2 >> 31));
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /* if x is 0s, we can use !! to covert x to 0 or 1, we know 0 | x will get x itself, so
     * we have two cases: x is not 0, we can convert it into 1, and << 31, then >> 31 to get all ones,
     * & this number with y, we can get y. */
    int condition = ~!!x;
    return ~(((condition + 1) & y) ^ ((condition + 1) | z));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int signOfX = (x>>31);
    int signOfY = (y>>31);
    int isSameSign = !(signOfX ^ signOfY);
    int negativeX = ~x + 1; 
    return (~isSameSign & !(signOfY)) | (isSameSign & !((negativeX + y) >> 31));   
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
    /* The sign of positive 0 and negative 0 are same, so we can use that property to determine whether the number is 0, and we must show that the sign bit of 0 is not 1. */
    int negativeX = ~x + 1;
    int signOfX = x >> 31;
    int signOfNegX = negativeX >> 31;
    return ((signOfX ^ signOfNegX) | signOfX) + 1  
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int y, result, mask16, mask8, mask4, mask2, mask1, bitnum;
    mask1 = 0x2; // 0x1 << 1
    mask2 = 0xC; // 0x3 << 2
    mask4 = 0xF0; // 0x00000F0;
    mask8 = 0xFF << 8; // 0x0000FF00;
    mask16 = (mask8 | 0xFF) << 16;

    result = 1;
    y = x ^ (x>>31);
        
    bitnum = !!((mask16 & y)<<4); 
    result += bitnum;
    y = y>>bitnum;

    bitnum = !!((mask8 & y)<<3);
    result += bitnum;
    y = y>>bitnum;

    bitnum = !!((mask4 & y)<<2); 
    result += bitnum;
    y = y >> bitnum;

    bitnum = !!((mask2 & y)<<1);
    result += bitnum;
    y = y >> bitnum;

    bitnum = !!(mask1 & y);
    result += bitnum;
    y = y >> bitnum;

    return result;
    // example: 0x11111100 => reverse: 0x00000011 rightShift: 1 << to the beginning of the number won't change the value of the number:
    // devarivation: 2^w-1 => right shift k; when we left shift one, the number minus 2^w, and plus 2^(w-1), so the whole number won't 
    // change. the the value of 0x11111100 is same as 0x100. when we negate 0x1111100, we can change all ones to zeros, so we can get
    // 0x0000011 to represent the needed number of the bits. and we can plus one in the end to represent the sign notation. 
}

//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    // There are some special cases we need to consider: Normalized and Denormalized.
    // If exp is all ones and M is not all zeros, we can Just return uf itself.
    // If exp is all ones and M is all zeros, we know it's infinite number.
    // If exp is all zeros, it's denormalized value, we can not just plus one on exp, because the M is 0. follow
    // significand number, so we can left shif 1, it maybe overflow though, we must consider this kind of situation.
    // If exp is neither zeros nor ones, we can get one normalized value, we can plus one on to exp directly,
    // e = 2 to the exp - bias, if plus one cause all ones, it will be denormalized value, we can return uf
    // itself directly. 
    unsigned expo = (uf >> 23) & 0xff;
    unsigned significand = (~((1 << 31) >> 24)) & uf;
    if (significand != 0 && expo == ~0) {
       return uf;
    }
    if (significand == 0) {
        return 0;
    }
    if (expo == 0) {
        int uncertainSig = significand << 1;
        if (uncertainSig < significand) {
            expo += 1; // before: 0.M times 2^1-expo, after: 1.M times 2^1-expo is same as left shift one on the significand. and the expo is not change. i.e. when we cause overflow, we get 1xxxxxxxx, and the first one is additional due to the property of the normalized value, xxxxxxxx won't change which means we just move the point to right one positon and the scale two is implemented.
        } else {
           significand = uncertainSig;
        }
    }
    if (expo != 0 && expo != ~0) {
       expo += 1;
       if (expo == ~0) {
           return uf;               
       }
    }
    return (exp << 23) + significand + (uf & (1 << 31));  
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    /* We can divide uf into two different parts: 1. The positive part, 2. The negative part.
     * if sign of uf is positive, we can roll down, if sign of uf is negative, we can roll up.
     * first, we can calculate the exp to catch the position of float point, and round the point number,
     *  */
    int sign = uf >> 31;
    int expMask = 0xff << 23;
    unsigned significand = (~((1 << 31) >> 24)) & uf;
    // if exp in range of 0x000.00 ~ 0x11..11, then we can calculate E by bias.
    int exp = expMask & uf;
    int E;
    int bias = 127;
    if (exp != 0 && exp != ~0) {
        E = exp - bias; 
    }
    // if E is in the range of (23, 31), we can get the right solution, if out of range, we will 
    // fail to represent.
    if (E > 31) {
        return 0x80000000u;
    }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    /* There are two ways to represent this expression, denormalized value, and normalized value:
     * and the significand 1.0000...000, 0.xxx...xxx where x can represent 1 which only appear once.
     * denormalized situation: exp is fixed: 1 - bias, and we can exchange the point position through
     * shifting position of one in significand. normalized situation: exp will change, but M can not change due to
     * the implied leading one. */ 
     
     // We start by denormalized situation.
     int Mass = 0x1<<22; // 0x0000......0001, The smallest precision we can represent. 1-bias=-127.
     if (x < -150) {
        return 0;
     } 
     if (x <= -128) {
        x += 128;
        x = ~x + 1;
        Mass = Mass >> x; 
        return Mass;
     }
     if (x > -128) {
         // Now the position of one is fixed due to the implied leading one.
         if (x > 254) {
            return +INF;
         }
     }
     return x << 23;
} 

