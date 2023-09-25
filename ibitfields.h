#ifndef _IBITFIELDS_H
#define _IBITFIELDS_H

/******************************************************************************\
|
| instruction bitfields
|
\******************************************************************************/

/*
 * the value of the indicated operand
 */
#define IBF_OP0         0x00
#define IBF_OP1         0x01
#define IBF_OP2         0x02
#define IBF_OP3         0x03
#define IBF_OP4         0x04
#define IBF_OP5         0x05
#define IBF_OP6         0x06
#define IBF_OP7         0x07

/*
 * the value of the indicated operand must be a multiple of 2
 */
#define IBF_OP0_MULT_2  0x08
#define IBF_OP1_MULT_2  0x09
#define IBF_OP2_MULT_2  0x0a
#define IBF_OP3_MULT_2  0x0b
#define IBF_OP4_MULT_2  0x0c
#define IBF_OP5_MULT_2  0x0d
#define IBF_OP6_MULT_2  0x0e
#define IBF_OP7_MULT_2  0x0f

/*
 * the value of the indicated operand must be a multiple of 4
 */
#define IBF_OP0_MULT_4  0x10
#define IBF_OP1_MULT_4  0x11
#define IBF_OP2_MULT_4  0x12
#define IBF_OP3_MULT_4  0x13
#define IBF_OP4_MULT_4  0x14
#define IBF_OP5_MULT_4  0x15
#define IBF_OP6_MULT_4  0x16
#define IBF_OP7_MULT_4  0x17

/*
 * the value of the indicated operand must be a multiple of 8
 */
#define IBF_OP0_MULT_8  0x18
#define IBF_OP1_MULT_8  0x19
#define IBF_OP2_MULT_8  0x1a
#define IBF_OP3_MULT_8  0x1b
#define IBF_OP4_MULT_8  0x1c
#define IBF_OP5_MULT_8  0x1d
#define IBF_OP6_MULT_8  0x1e
#define IBF_OP7_MULT_8  0x1f

/*
 * constant values from 0 to 7
 */
#define IBF_CONST_0     0x20
#define IBF_CONST_1     0x21
#define IBF_CONST_2     0x22
#define IBF_CONST_3     0x23
#define IBF_CONST_4     0x24
#define IBF_CONST_5     0x25
#define IBF_CONST_6     0x26
#define IBF_CONST_7     0x27

/*
 * the value of the indicated operand must be a multiple of 2, shift right 1
 */
#define IBF_OP0_SHFT_1  0x28
#define IBF_OP1_SHFT_1  0x29
#define IBF_OP2_SHFT_1  0x2a
#define IBF_OP3_SHFT_1  0x2b
#define IBF_OP4_SHFT_1  0x2c
#define IBF_OP5_SHFT_1  0x2d
#define IBF_OP6_SHFT_1  0x2e
#define IBF_OP7_SHFT_1  0x2f

/*
 * the value of the indicated operand must be a multiple of 4, shift right 2
 */
#define IBF_OP0_SHFT_2  0x30
#define IBF_OP1_SHFT_2  0x31
#define IBF_OP2_SHFT_2  0x32
#define IBF_OP3_SHFT_2  0x33
#define IBF_OP4_SHFT_2  0x34
#define IBF_OP5_SHFT_2  0x35
#define IBF_OP6_SHFT_2  0x36
#define IBF_OP7_SHFT_2  0x37

/*
 * the value of the indicated operand must be a multiple of 8, shift right 3
 */
#define IBF_OP0_SHFT_3  0x38
#define IBF_OP1_SHFT_3  0x39
#define IBF_OP2_SHFT_3  0x3a
#define IBF_OP3_SHFT_3  0x3b
#define IBF_OP4_SHFT_3  0x3c
#define IBF_OP5_SHFT_3  0x3d
#define IBF_OP6_SHFT_3  0x3e

/*
 * program counter relative displacement
 */
#define IBF_OP0_DISP    0x40
#define IBF_OP1_DISP    0x41
#define IBF_OP2_DISP    0x42
#define IBF_OP3_DISP    0x43
#define IBF_OP4_DISP    0x44
#define IBF_OP5_DISP    0x45
#define IBF_OP6_DISP    0x46
#define IBF_OP7_DISP    0x47

/*
 * instruction opcode
 */
#define IBF_OPCODE      0xfe

/*
 * bitfield array end marker
 */
#define IBF_END         0xff

struct instr_bitfield
{
    u_int8_t width;
    u_int8_t type;
};


/*
 * zero operand
 */

extern struct instr_bitfield const flds_intrinsic[];


/*
 * one operand
 */

/* jump and call instructions */
extern struct instr_bitfield const flds_jmp[];
extern struct instr_bitfield const flds_scall_sjmp[];
extern struct instr_bitfield const flds_lcall_ljmp[];

/* single register instructions */
extern struct instr_bitfield const flds_bytereg[];
extern struct instr_bitfield const flds_wordreg[];
extern struct instr_bitfield const flds_longreg[];

/* one operand word */
extern struct instr_bitfield const flds_1op_waop_direct[];
extern struct instr_bitfield const flds_1op_waop_direct_long[];
extern struct instr_bitfield const flds_1op_waop_immediate[];
extern struct instr_bitfield const flds_1op_waop_indirect[];
extern struct instr_bitfield const flds_1op_waop_indirect_auto_inc[];
extern struct instr_bitfield const flds_1op_waop_indexed[];
extern struct instr_bitfield const flds_1op_waop_indexed_long[];


/*
 * two operand
 */

/* normalize instruction */
extern struct instr_bitfield const flds_norml[];

/* decrement and jump if not zero instruction */
extern struct instr_bitfield const flds_djnz[];

/* shift instructions */
extern struct instr_bitfield const flds_byteshft[];
extern struct instr_bitfield const flds_wordshft[];
extern struct instr_bitfield const flds_longshft[];

/* two operand byte */
extern struct instr_bitfield const flds_2op_baop_direct[];
extern struct instr_bitfield const flds_2op_baop_direct_long[];
extern struct instr_bitfield const flds_2op_baop_immediate[];
extern struct instr_bitfield const flds_2op_baop_indirect[];
extern struct instr_bitfield const flds_2op_baop_indirect_auto_inc[];
extern struct instr_bitfield const flds_2op_baop_indexed[];
extern struct instr_bitfield const flds_2op_baop_indexed_long[];

/* two operand byte/word */
extern struct instr_bitfield const flds_2op_baopw_direct[];
extern struct instr_bitfield const flds_2op_baopw_direct_long[];
extern struct instr_bitfield const flds_2op_baopw_immediate[];
extern struct instr_bitfield const flds_2op_baopw_indirect[];
extern struct instr_bitfield const flds_2op_baopw_indirect_auto_inc[];
extern struct instr_bitfield const flds_2op_baopw_indexed[];
extern struct instr_bitfield const flds_2op_baopw_indexed_long[];

/* prefixed two operand byte/word */
extern struct instr_bitfield const flds_pre_2op_baopw_direct[];
extern struct instr_bitfield const flds_pre_2op_baopw_direct_long[];
extern struct instr_bitfield const flds_pre_2op_baopw_immediate[];
extern struct instr_bitfield const flds_pre_2op_baopw_indirect[];
extern struct instr_bitfield const flds_pre_2op_baopw_indirect_auto_inc[];
extern struct instr_bitfield const flds_pre_2op_baopw_indexed[];
extern struct instr_bitfield const flds_pre_2op_baopw_indexed_long[];

/* two operand word */
extern struct instr_bitfield const flds_2op_waop_direct[];
extern struct instr_bitfield const flds_2op_waop_direct_long[];
extern struct instr_bitfield const flds_2op_waop_immediate[];
extern struct instr_bitfield const flds_2op_waop_indirect[];
extern struct instr_bitfield const flds_2op_waop_indirect_auto_inc[];
extern struct instr_bitfield const flds_2op_waop_indexed[];
extern struct instr_bitfield const flds_2op_waop_indexed_long[];

/* two operand word/long */
extern struct instr_bitfield const flds_2op_waopl_direct[];
extern struct instr_bitfield const flds_2op_waopl_direct_long[];
extern struct instr_bitfield const flds_2op_waopl_immediate[];
extern struct instr_bitfield const flds_2op_waopl_indirect[];
extern struct instr_bitfield const flds_2op_waopl_indirect_auto_inc[];
extern struct instr_bitfield const flds_2op_waopl_indexed[];
extern struct instr_bitfield const flds_2op_waopl_indexed_long[];

/* prefixed two operand word/long */
extern struct instr_bitfield const flds_pre_2op_waopl_direct[];
extern struct instr_bitfield const flds_pre_2op_waopl_direct_long[];
extern struct instr_bitfield const flds_pre_2op_waopl_immediate[];
extern struct instr_bitfield const flds_pre_2op_waopl_indirect[];
extern struct instr_bitfield const flds_pre_2op_waopl_indirect_auto_inc[];
extern struct instr_bitfield const flds_pre_2op_waopl_indexed[];
extern struct instr_bitfield const flds_pre_2op_waopl_indexed_long[];


/*
 * three operand
 */

/* jump on bit clear or set */
extern struct instr_bitfield const flds_jbc_jbs[];

/* three operand byte */
extern struct instr_bitfield const flds_3op_baop_direct[];
extern struct instr_bitfield const flds_3op_baop_direct_long[];
extern struct instr_bitfield const flds_3op_baop_immediate[];
extern struct instr_bitfield const flds_3op_baop_indirect[];
extern struct instr_bitfield const flds_3op_baop_indirect_auto_inc[];
extern struct instr_bitfield const flds_3op_baop_indexed[];
extern struct instr_bitfield const flds_3op_baop_indexed_long[];

/* three operand byte/word */
extern struct instr_bitfield const flds_3op_baopw_direct[];
extern struct instr_bitfield const flds_3op_baopw_direct_long[];
extern struct instr_bitfield const flds_3op_baopw_immediate[];
extern struct instr_bitfield const flds_3op_baopw_indirect[];
extern struct instr_bitfield const flds_3op_baopw_indirect_auto_inc[];
extern struct instr_bitfield const flds_3op_baopw_indexed[];
extern struct instr_bitfield const flds_3op_baopw_indexed_long[];

/* prefixed three operand byte/word */
extern struct instr_bitfield const flds_pre_3op_baopw_direct[];
extern struct instr_bitfield const flds_pre_3op_baopw_direct_long[];
extern struct instr_bitfield const flds_pre_3op_baopw_immediate[];
extern struct instr_bitfield const flds_pre_3op_baopw_indirect[];
extern struct instr_bitfield const flds_pre_3op_baopw_indirect_auto_inc[];
extern struct instr_bitfield const flds_pre_3op_baopw_indexed[];
extern struct instr_bitfield const flds_pre_3op_baopw_indexed_long[];

/* three operand word */
extern struct instr_bitfield const flds_3op_waop_direct[];
extern struct instr_bitfield const flds_3op_waop_direct_long[];
extern struct instr_bitfield const flds_3op_waop_immediate[];
extern struct instr_bitfield const flds_3op_waop_indirect[];
extern struct instr_bitfield const flds_3op_waop_indirect_auto_inc[];
extern struct instr_bitfield const flds_3op_waop_indexed[];
extern struct instr_bitfield const flds_3op_waop_indexed_long[];

/* three operand word/long */
extern struct instr_bitfield const flds_3op_waopl_direct[];
extern struct instr_bitfield const flds_3op_waopl_direct_long[];
extern struct instr_bitfield const flds_3op_waopl_immediate[];
extern struct instr_bitfield const flds_3op_waopl_indirect[];
extern struct instr_bitfield const flds_3op_waopl_indirect_auto_inc[];
extern struct instr_bitfield const flds_3op_waopl_indexed[];
extern struct instr_bitfield const flds_3op_waopl_indexed_long[];

/* prefixed three operand word/long */
extern struct instr_bitfield const flds_pre_3op_waopl_direct[];
extern struct instr_bitfield const flds_pre_3op_waopl_direct_long[];
extern struct instr_bitfield const flds_pre_3op_waopl_immediate[];
extern struct instr_bitfield const flds_pre_3op_waopl_indirect[];
extern struct instr_bitfield const flds_pre_3op_waopl_indirect_auto_inc[];
extern struct instr_bitfield const flds_pre_3op_waopl_indexed[];
extern struct instr_bitfield const flds_pre_3op_waopl_indexed_long[];

#endif // _IBITFIELDS_H
