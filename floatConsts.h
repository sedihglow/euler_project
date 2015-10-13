#ifndef _FLOATCONSTS_H
#define _FLOATCONSTS_H

#include <sys/types.h>
#include <string.h>

/* Use memcpy to set a float value, causing the proper value to appear instead
   of the min/max. (example: Nan, -Nan, etc.), (memset gives improper results) */
#define set_float(num, set)    memcpy(&num, &set, sizeof(num))
#define set_double(num, set)   set_float(num,set)
#define set_nan(num, set)      set_float(num, set)
#define set_inf(num, set)      set_float(num,set)

/* Use these definitions placed in memory for the above macros in set.
   example: int32_t fnan = PF_NAN;
           int64_t dnegInf = ND_INF;

           set_float(num, fnan);
           set_double(num, dneginf); */

/* 32 bit float */
#define PF_NAN  0x7fc00000
#define NF_NAN  0xffc00000

#define PF_INF  0x7f800000
#define NF_INF  0xff800000

/* 64 bit double */
#define PD_NAN  0x7ff8000000000000
#define ND_NAN  0xfff8000000000000

#define PD_INF  0x7ff0000000000000
#define ND_INF  0xfff0000000000000

#endif
