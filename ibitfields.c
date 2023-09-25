#include <stdio.h>
#include <stdlib.h>

#include "ibitfields.h"

/******************************************************************************\
|
| instruction bitfields
|
\******************************************************************************/

/*
 * zero operand
 */

struct instr_bitfield const flds_intrinsic[] =
{
    {  8, IBF_OPCODE },
    {  0, IBF_END },
};


/*
 * one operand
 */

/* jump and call instructions */
struct instr_bitfield const flds_jmp[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP0_DISP },
    {  0, IBF_END }
};

struct instr_bitfield const flds_scall_sjmp[] =
{
    {  5, IBF_OPCODE },
    { 11, IBF_OP0_DISP },
    {  0, IBF_END },
};

struct instr_bitfield const flds_lcall_ljmp[] =
{
    {  8, IBF_OPCODE },
    { 16, IBF_OP0_DISP },
    {  0, IBF_END },
};

/* single register instructions */
struct instr_bitfield const flds_bytereg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP0 },
    {  0, IBF_END },
};

struct instr_bitfield const flds_wordreg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_longreg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END },
};

/* one operand word */
struct instr_bitfield const flds_1op_waop_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP0_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP0_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_1op_waop_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/*
 * two operand
 */

/* normalize instruction */
struct instr_bitfield const flds_norml[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END },
};

/* decrement and jump if not zero instruction */
struct instr_bitfield const flds_djnz[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP0 },
    {  8, IBF_OP1_DISP },
    {  0, IBF_END }
};

/* shift instructions */
struct instr_bitfield const flds_byteshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END },
};


struct instr_bitfield const flds_wordshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END },
};


struct instr_bitfield const flds_longshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END },
};

/* two operand byte */
struct instr_bitfield const flds_2op_baop_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baop_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

/* two operand byte/word */
struct instr_bitfield const flds_2op_baopw_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_baopw_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* prefixed two operand byte/word */
struct instr_bitfield const flds_pre_2op_baopw_direct[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_immediate[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_indirect[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_indirect_auto_inc[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_indexed[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_direct_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_baopw_indexed_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* two operand word */
struct instr_bitfield const flds_2op_waop_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waop_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* two operand word/long */
struct instr_bitfield const flds_2op_waopl_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_2op_waopl_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

/* prefixed two operand word/long */
struct instr_bitfield const flds_pre_2op_waopl_direct[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_immediate[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_indirect[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_indirect_auto_inc[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP1_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_indexed[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_direct_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_2op_waopl_indexed_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

/*
 * three operand
 */

/* jump on bit clear or set */
struct instr_bitfield const flds_jbc_jbs[] =
{
    {  5, IBF_OPCODE },
    {  3, IBF_OP1 },      /* bit      */
    {  8, IBF_OP0 },      /* register */
    {  8, IBF_OP2_DISP },
    {  0, IBF_END }
};

/* three operand byte */
struct instr_bitfield const flds_3op_baop_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baop_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0 },
    {  0, IBF_END }
};

/* three operand byte/word */
struct instr_bitfield const flds_3op_baopw_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_baopw_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* prefixed three operand byte/word */
struct instr_bitfield const flds_pre_3op_baopw_direct[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_immediate[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_indirect[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_indirect_auto_inc[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_indexed[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_direct_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_baopw_indexed_long[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* three operand word */
struct instr_bitfield const flds_3op_waop_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waop_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_2 },
    {  0, IBF_END }
};

/* three operand word/long */
struct instr_bitfield const flds_3op_waopl_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_3op_waopl_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

/* prefixed three operand word/long */
struct instr_bitfield const flds_pre_3op_waopl_direct[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_immediate[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_1 },
    { 16, IBF_OP2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_indirect[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_indirect_auto_inc[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_2 },
    {  7, IBF_OP2_SHFT_1 },
    {  1, IBF_CONST_1 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_indexed[] =
{
    { 14, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_0 },
    {  8, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_direct_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};

struct instr_bitfield const flds_pre_3op_waopl_indexed_long[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_CONST_3 },
    {  7, IBF_OP3_SHFT_1 },
    {  1, IBF_CONST_1 },
    { 16, IBF_OP2_MULT_2 },
    {  8, IBF_OP1_MULT_2 },
    {  8, IBF_OP0_MULT_4 },
    {  0, IBF_END }
};
