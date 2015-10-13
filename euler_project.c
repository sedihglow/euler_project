/*
    implements the problems yo. All helper functions will be static, and 
    each problem and its functions are seperated by comments */


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
/*#define NDEBUG*/
#include <assert.h>

#include "euler_project.h"



                    /* Problem 1 */
void prob1()/*#{{{*/
{
#define FIND_TILL 1000
    register uint32_t multSum = 0;  /* sum of all multiples found */
    register int32_t findMult = 0; /* current multiple to go from */
    register int32_t i = 0;

    /* 3 and 5 have multiples that are the same. These duplicate multiples
       should not be counted more than once. 

       Example: 30 should only be added to multSum once, not the twice it 
                appears */

    findMult = 3;
    for(i = findMult; i < FIND_TILL; i += findMult)
    {
        multSum += i; 
    }
    
    findMult = 5;
    for(i = findMult; i < FIND_TILL; i += findMult)
    {
        if(i % 3 != 0){
            multSum += i;}
    } 

    /* the alternate solution is 1 loop (could be a while), going through every
       number, with and if statment that say if((i % 3 == 0) || (i % 5 == 0)) */

    printf("\nmultSum of all the multiples of %d is %u\n",FIND_TILL, multSum);
#undef FIND_TILL
} /* end prob1 #}}} */

                    /* Problem 2 */
void prob2()/*#{{{*/
{
#define FS_LIMIT    4000000
    register uint32_t prev = 0;    /* current sequence - 1 place. */
    register uint32_t temp = 0;    /* used to set prev */
    register uint32_t sum = 0;     /* sum of even numbers in squence */ 
    register uint32_t i = 0;       /* current number in squence. */

    for(i = 1, prev = 1; i < FS_LIMIT; i += prev, prev = temp)
    {
        temp = i;
        /* if true, number is even */
        if((i & 1) == 0){
            sum += i;}
    }

    /* OPTIMIZATION NOTE: It is a proof that in the F sequence, every third
                          number will be an even number. With this knowlege
                          we can remove the check for even number. 
                          
                          To do this we just move to the next third value in the
                          sequence every iteration in a while loop, adding
                          the sum at the start of the iteration, then progressing
                          the required variables to the third sequence from 
                          the current value */

    printf("\nSum of the even terms in the F sequence under 4million: %d\n", sum);
#undef FS_LIMIT
} /* end prob2 #}}} */

                    /* Problem 3 */ /* square root */
static double squareRoot(double toSqrt)/*#{{{*/
{
    /* i wanted to get an algorithm to find the square root of a number without
       using the math.h header. I found online that there are various ways to
       do this, but newtons method for finding square roots is quite fast.
       
       Newtons method: E = x - f(x)/f'(x), NOTE ON ESTIMATION: 
                                           where E is the new estimate and
       //Find f(x) f'(x)                   x is its "initial" estimate, closer
       sqrt(n) = x;                        to the actual value. The more we go
       therefore, x^2 = n;                 through this, the closer we get to
       f(x) = (x^2) - n;                   the true square root.
       f'(x) = 2x;
       
       So in newtons method, y = x - (x^2 - n) / 2x
    */
    register uint64_t negNan = ND_NAN;

    register double estimate = 0.0;
    register double newEstimate = 0.0;

    if(toSqrt < 0){
        return negNan;}

    if(toSqrt == 0){
        return 0;}

    newEstimate = toSqrt;
    estimate = toSqrt/2; /* estimate can be made closer to the expected value
                            but the number to square will also work, just takes
                            more run time. Basically changing this will improve
                            performace, but still garunteed if starting at the
                            number to square.*/

    /* NOTE: There may be a situation where i should limit the loop cycle for
             whatever reason. Just add a counter in those situations.
        #define LOOP_COUNT
        #undef LOOP_COUNT */
    do
    {
        newEstimate = estimate - (estimate*estimate - toSqrt) / (2*estimate);
        estimate = newEstimate;
    }while(toSqrt/newEstimate + 0.0001 < estimate);
    
    return newEstimate;
} /* end squareRoot #}}} */

#define int64sqrt 
#ifndef int64sqrt
/* 64bit "integer square root" */
static uint64_t int64Sqrt(const uint64_t toSqrt)/*#{{{*/
{
    /* This function finds the largest integer X whose Square is less than A.
       Known as the Integer Square Root. Good on systems that are limited.
       Downfall is overall speed. */
    register uint64_t square = 1;    /* value of square root occurs in the row 
                                        following i <= toSquare */
    register uint64_t delta = 3;     /* Difference between successive squares.
                                        The sequence of odd numbers. */
    for(square = 1; square <= toSqrt; square += delta){
        delta += 2; }
    
    /* value of square root, 1 row following what i calculated */
    return (delta/2 - 1);
} /* end int64Sqrt #}}} */
#endif

/* check if a number is a prime number
   NOTE: Theres better mathy versions than what i originally wrote.
         All prime numbers greater than 3 can be written as 6k+/-1,
         One of the handle Seive of E. Or the other modulo one is faster if
         you have a good target guess or something. */
static int64_t isPrime(const int64_t toCheck)/*#{{{*/
{
    /* There are various algorithms to do this with different trade offs. 
       I am going based on a simple math algorithm to find if a number is prime
       with division.
       
       algorithm: If the number is n, then dividing it by every prime number
                  less than or equal to sqrt(n) and showing that there is no
                  remainder. */
    register uint32_t sqrtCheck = 0.0; /* originally was a double. */
    register uint32_t i = 0;

    /* the if statments without mod are cheaper than with mod */
    
    if(toCheck < 2){ /* 0 and 1 are not prime */
        return 0;}

    if(toCheck < 4){
        return 1;} /* 2 and 3 are prime */

    /* this takes into account 4, 6 and 8, and all even numbers */
    if((toCheck % 2) == 0){
        return 0;}
    
    if(toCheck < 9){
        return 1;} /* 5,7 */

    if((toCheck % 3) == 0){
        return 0;}
    
    sqrtCheck = (uint32_t) squareRoot(toCheck); /* kills the float */
    for(i = 5; i <= sqrtCheck; i += 6) /* increment by 6, +2 and +4 handled in loop */
    {
        /* If the mod is 0, a multiple was found. */
        if((toCheck % i) == 0){
            return 0;} /* not prime */
        if((toCheck % (i+2)) == 0){
            return 0;}
    }

   return 1;
} /* end isPrime #}}} */

/* written to find the Largest Prime Factoral of ANY number, not just the prob. */
void prob3()/*#{{{*/
{
    /* We are looking for the largest prime factor.
       Example: 12. The prime factors are 2x2x3. The answer is 3. */
#define LPF_NUM    600851475143
    /* ints are okay because it will not divide unless the number is even due
       to the mod value. It must be a multiple before the division, resulting
       in even numbers, not floats or doubles */
    register int64_t prFact = LPF_NUM;
    register int64_t prime = 0;
    
    if(isPrime(prFact) == 1)
    {
        printf("\nresult: %" PRIi64 "\n", prFact);
        return;
    }

    prime = 2;
    while((prFact % prime) == 0){
        prFact /= prime;
    }
   
    prime = 3;
    while(prFact > 1) /* example, prFact = 6, prime = 3. prFact /= prime is 1 */
    {
        if(prFact % prime == 0){
            prFact /= prime;}
        else{
            prime += 2;}
    }
    
    printf("\n2: The highest prime factoral is: %" PRIi64 "\n", prime);

#undef LPF_NUM
} /* end prob3 #}}} */

                    /* problem 4 */
#define digit
#ifndef digit
/* count the number of digits in a given int */
static inline uint32_t dec32_tDigCnt(register int32_t num, register int32_t base)/*#{{{*/
{
    register uint32_t cnt = 0;

    while(num > 0)
    {
        num /= base;
        ++count;
    }

    return count;
} /* end 32_tDigCnt #}}} */
#endif

/* reverse an integer without converting to a string, positive numbers */
static uint32_t reverse_int(register uint32_t num)/*#{{{*/
{
    register uint32_t res = 0;

    /* if taking in an int, ensure num >= 0 */

    while(num > 0)
    {
        res = (res*10) + (num % 10);
        num /= 10;
    }

    return res;
} /* end reverse_int #}}} */

void prob4()/*#{{{*/
{
#define PAL_NUM    998001    /* 999 * 999 */
#define LIM        9801      /* 99 * 99 */
    register uint32_t i = 0;
    register uint32_t num = PAL_NUM;
    register uint32_t res = 0;

    /* this algorithm will only work on numbers whose digits are even. 
       See dec32_tDigCnt */

    /* set num to nearest multiple of 11 below PAL_NUM */
    while((num % 11) > 0){
        --num;}

    /* we know every decrement will be a multiple of 11. Even numbered digit 
       pal num's are divisible by 11 */
    for(/*num*/; num > LIM; num -= 11)
    {
        /* check if num is a pal */
        if(reverse_int(num) == num)
        {
            /* 200 comes from 500*200, 10000, first 6 digit num in 3dig*3dig */
            for(i = 999; i > 200; --i)
            {
                if((num % i) == 0 && (res = num/i) < 1000)
                {
                    printf("\npal. num: %d = %d x %d\n",num, i, num/i);
                    return;
                } /* end if */
            } /* end for */
        } /* end if */
    } /* end for */
#undef PAL_NUM
#undef LIM
} /* end prob4 #}}} */

                    /* problem 5 */
void prob5()/*#{{{*/
{
    register uint32_t num = 0;
    
    /* note: INT_MAX is not divisible by 20, so when num > INT_MAX - 20, we
             are still in the range of an int. */
    for(num = 20;  num < (INT_MAX - 20); num += 20)
    {
        if(((num % 19) == 0) && 
           ((num % 18) == 0) &&
           ((num % 17) == 0) &&
           ((num % 16) == 0) &&
           ((num % 15) == 0) &&
           ((num % 14) == 0) &&
           ((num % 13) == 0) &&
           ((num % 12) == 0) &&
           ((num % 11) == 0)) 
        {
            printf("\nlowest num divisible by 1-20 is %d\n",num);
            return;
        } /* end if */
    } /* end for */

    fputs("\nOut of range of integer\n",stderr);
} /* end prob5 #}}} */

                    /* problem 6 */
/* uses 2 equations. Sum 1+2+..+n, and sum the squares of each number 1-n, see
   problem description and equations used */
void prob6()/*#{{{*/
{
    int64_t n = 0;        /* natural number */
    int64_t natSum = 0;   /* sum of natural numbers 1-100, to be squared */
    int64_t sqSum = 0;    /* sum of each squared natural number 1-100 */
    
    /* my original solution, inefficient.
    for(n = 1; n < 101; ++n)
    {
        natSum += n;    
        sqSum += (n*n); 
    }
    natSum *= natSum;
    printf("\nSquared each sum: %"PRId64"\nNatural sum squared: %"PRId64"\n"
           "Difference: %"PRId64"\n", sqSum,natSum,natSum-sqSum);
    */

    /* Best solution using mathmatical proofs i didnt know. */
    n = 100;
    natSum = (n*(n+1))/2;
    sqSum = ((2*n + 1)*(n + 1)*n)/6;
    
    natSum *= natSum;
    printf("\nSquared each sum: %"PRId64"\nNatural sum squared: %"PRId64"\n"
           "Difference: %"PRId64"\n", sqSum,natSum,natSum-sqSum);
} /* end prob6 #}}} */

                    /* problem 7 */
void prob7()/*#{{{*/
{
#define FIND 10001
    uint64_t prime = 1;    /* the found prime number */
    uint64_t count = 0;    /* counts how many primes have been found */
    
    count = 1; /* accounts for prime 2, which we skip */

    do
    {
        prime += 2; /* if this was below if, then prime would increment by 2
                       after count hits FIND */
        if(isPrime(prime) == 1){
            ++count;}
    }while(count < FIND);

    printf("\nThe %"PRId64"st prime is %"PRId64"\n", count, prime);
#undef FIND
} /* end prob7 #}}} */

                    /* problem 8 */
void prob8()/*#{{{*/
{
/* original solution uses way to many variables, therefore too much
   potential memory to hold the variables. Granted most will probably be
   in a register, still. */
   
    uint8_t workNum[1000] = 
                      /* number to work with, too big for iso 90 --; #{{{ */
                     {7,3,1,6,7,1,7,6,5,3,1,3,3,0,6,2,4,9,1,9,2,2,5,1,1,9,6,7,
                      4,4,2,6,5,7,4,7,4,2,3,5,5,3,4,9,1,9,4,9,3,4,9,6,9,8,3,5,
                      2,0,3,1,2,7,7,4,5,0,6,3,2,6,2,3,9,5,7,8,3,1,8,0,1,6,9,8,
                      4,8,0,1,8,6,9,4,7,8,8,5,1,8,4,3,8,5,8,6,1,5,6,0,7,8,9,1,
                      1,2,9,4,9,4,9,5,4,5,9,5,0,1,7,3,7,9,5,8,3,3,1,9,5,2,8,5,
                      3,2,0,8,8,0,5,5,1,1,1,2,5,4,0,6,9,8,7,4,7,1,5,8,5,2,3,8,
                      6,3,0,5,0,7,1,5,6,9,3,2,9,0,9,6,3,2,9,5,2,2,7,4,4,3,0,4,
                      3,5,5,7,6,6,8,9,6,6,4,8,9,5,0,4,4,5,2,4,4,5,2,3,1,6,1,7,
                      3,1,8,5,6,4,0,3,0,9,8,7,1,1,1,2,1,7,2,2,3,8,3,1,1,3,6,2,
                      2,2,9,8,9,3,4,2,3,3,8,0,3,0,8,1,3,5,3,3,6,2,7,6,6,1,4,2,
                      8,2,8,0,6,4,4,4,4,8,6,6,4,5,2,3,8,7,4,9,3,0,3,5,8,9,0,7,
                      2,9,6,2,9,0,4,9,1,5,6,0,4,4,0,7,7,2,3,9,0,7,1,3,8,1,0,5,
                      1,5,8,5,9,3,0,7,9,6,0,8,6,6,7,0,1,7,2,4,2,7,1,2,1,8,8,3,
                      9,9,8,7,9,7,9,0,8,7,9,2,2,7,4,9,2,1,9,0,1,6,9,9,7,2,0,8,
                      8,8,0,9,3,7,7,6,6,5,7,2,7,3,3,3,0,0,1,0,5,3,3,6,7,8,8,1,
                      2,2,0,2,3,5,4,2,1,8,0,9,7,5,1,2,5,4,5,4,0,5,9,4,7,5,2,2,
                      4,3,5,2,5,8,4,9,0,7,7,1,1,6,7,0,5,5,6,0,1,3,6,0,4,8,3,9,
                      5,8,6,4,4,6,7,0,6,3,2,4,4,1,5,7,2,2,1,5,5,3,9,7,5,3,6,9,
                      7,8,1,7,9,7,7,8,4,6,1,7,4,0,6,4,9,5,5,1,4,9,2,9,0,8,6,2,
                      5,6,9,3,2,1,9,7,8,4,6,8,6,2,2,4,8,2,8,3,9,7,2,2,4,1,3,7,
                      5,6,5,7,0,5,6,0,5,7,4,9,0,2,6,1,4,0,7,9,7,2,9,6,8,6,5,2,
                      4,1,4,5,3,5,1,0,0,4,7,4,8,2,1,6,6,3,7,0,4,8,4,4,0,3,1,9,
                      9,8,9,0,0,0,8,8,9,5,2,4,3,4,5,0,6,5,8,5,4,1,2,2,7,5,8,8,
                      6,6,6,8,8,1,1,6,4,2,7,1,7,1,4,7,9,9,2,4,4,4,2,9,2,8,2,3,
                      0,8,6,3,4,6,5,6,7,4,8,1,3,9,1,9,1,2,3,1,6,2,8,2,4,5,8,6,
                      1,7,8,6,6,4,5,8,3,5,9,1,2,4,5,6,6,5,2,9,4,7,6,5,4,5,6,8,
                      2,8,4,8,9,1,2,8,8,3,1,4,2,6,0,7,6,9,0,0,4,2,2,4,2,1,9,0,
                      2,2,6,7,1,0,5,5,6,2,6,3,2,1,1,1,1,1,0,9,3,7,0,5,4,4,2,1,
                      7,5,0,6,9,4,1,6,5,8,9,6,0,4,0,8,0,7,1,9,8,4,0,3,8,5,0,9,
                      6,2,4,5,5,4,4,4,3,6,2,9,8,1,2,3,0,9,8,7,8,7,9,9,2,7,2,4,
                      4,2,8,4,9,0,9,1,8,8,8,4,5,8,0,1,5,6,1,6,6,0,9,7,9,1,9,1,
                      3,3,8,7,5,4,9,9,2,0,0,5,2,4,0,6,3,6,8,9,9,1,2,5,6,0,7,1,
                      7,6,0,6,0,5,8,8,6,1,1,6,4,6,7,1,0,9,4,0,5,0,7,7,5,4,1,0,
                      0,2,2,5,6,9,8,3,1,5,5,2,0,0,0,5,5,9,3,5,7,2,9,7,2,5,7,1,
                      6,3,6,2,6,9,5,6,1,8,8,2,6,7,0,4,2,8,2,5,2,4,8,3,6,0,0,8,
                      2,3,2,5,7,5,3,0,4,2,0,7,5,2,9,6,3,4,5,0}; /*#}}}*/
   /* 
    uint32_t i = 0;
    uint32_t k = 0;
    uint64_t prodSum = 1;
    uint64_t largeSum = 0;
    uint8_t *lrgSt = NULL;
    uint8_t *start = NULL;
    uint8_t *current = NULL;
 
    start = workNum;
    for(i = 0; i < 1000-12; ++i)
    {
        current = start;
        prodSum = 1;
        for(k = 0; k < 13; ++k)
        {
            prodSum *= *current;
            if(prodSum == 0){
                k = 13;}
            ++current;
        } 

        if(prodSum > largeSum)
        {
            largeSum = prodSum;
            lrgSt = start;
        }  

        ++start;
    } 

    puts("\n");
    for(k=0; k < 13; ++k){
        printf("%d",lrgSt[k]);} 
        printf(" = %llu", largeSum);
    puts("\n");
*/

/* more lean solution, doesnt use pointers, doesnt print the 13 numbers */
    uint32_t i = 0;
    uint32_t k = 0;
    uint64_t prodSum = 0;
    uint64_t result = 0;


    for(i = 0; i < 1000-13; ++i) 
    {
        /* right side probably overflows or some shit */
        /*prodSum = workNum[i]   * workNum[i+1] * workNum[i+2]  * workNum[i+3] *
                  workNum[i+4] * workNum[i+5] * workNum[i+6]  * workNum[i+7] *
                  workNum[i+8] * workNum[i+9] * workNum[i+10] * workNum[i+11]*
                  workNum[i+12];*/

        prodSum = 1;
        for(k = 0; k < 13; ++k)
        {
            prodSum *= workNum[i + k];
        }

        if(prodSum == 23514624000)
        {
            printf("winner\n");
        }

        if(prodSum > result)
        {
            result = prodSum;
            printf("inside %d: %d: %llu\n", i, workNum[i], result);        
        }
    }

    printf("%llu\n", result);        
} /* end prob8 #}}} */

                    /* problem 9 */
void prob9()/*#{{{*/
{
    uint32_t result = 0;

    for(;;)
    {

        for(;;)
        {
        }
    }

} /* end prob9 #}}} */



