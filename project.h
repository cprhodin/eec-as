#ifndef _PROJECT_H
#define _PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u_int_t;

#define YYDEBUG 1

typedef struct obj_desc * YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define yystype YYSTYPE /* obsolescent; will be withdrawn */
#define YYSTYPE_IS_DECLARED 1

extern int yydebug;

#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define LSB_MASK(a) ((0x1 << (a)) - 1)
#define swap16(a) ((((a) >> 8) & 0xff) | (((a) & 0xff) << 8))
#define _BV(x) (1<<x)
#define calloc_object(a) (a *) calloc(1, sizeof(a))

#define inrange(a,b,c) (((b)->defined) && ((int)((b)->value) >= (int)(a)) && ((int)((b)->value) <= (int)(c)))

#endif // _PROJECT_H
