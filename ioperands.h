#ifndef _IOPERANDS_H
#define _IOPERANDS_H

#define MAX_FIELDS 8


#define AOP_BYTE_DIRECT         1   // "addb",
#define AOP_WORD_DIRECT         1   // "add",
#define AOP_BYTE_DIRECT_LONG    3
#define AOP_WORD_DIRECT_LONG    3
#define AOP_BYTE_IMMEDIATE      1
#define AOP_WORD_IMMEDIATE      2
#define AOP_INDIRECT            1
#define AOP_INDIRECT_AUTO_INC   1
#define AOP_BYTE_INDEXED        2
#define AOP_WORD_INDEXED        2
#define AOP_BYTE_INDEXED_LONG   3
#define AOP_WORD_INDEXED_LONG   3
#define REG_BYTE
#define REG_WORD
#define REG_LONG
#define CADD                    // -128 to 127
#define CADD_SHORT              // -1024 to 1023
#define CADD_LONG               // -32768 to 32767
#define BITNO                   // 0 to 7
#define SHIFT_COUNT             // 0 to 15
#define SHIFT_REG               // r16 to r255


// "add"  + OPFMT_2OP_DIRECT             * DIRECT or DIRECT_LONG
// "add"  + OPFMT_2OP_IMMEDIATE
// "add"  + OPFMT_2OP_INDIRECT
// "add"  + OPFMT_2OP_INDIRECT_AUTO_INC
// "add"  + OPFMT_2OP_INDEXED            * INDEXED or INDEXED_LONG


// "add"  + ADDRMD_2OP_DIRECT            = REG_WORD, AOP_WORD_DIRECT        2 + 1  6,2,8,8       opcode aop reg          reg
// "add"  + ADDRMD_2OP_DIRECT_LONG       = REG_WORD, AOP_WORD_DIRECT_LONG   2 + 3  6,2,8,16,8    opcode aop 0   1 offset reg
// "add"  + ADDRMD_2OP_IMMEDIATE         = REG_WORD, AOP_WORD_IMMEDIATE     2 + 2  6,2,16,8
// "add"  + ADDRMD_2OP_INDIRECT          = REG_WORD, AOP_INDIRECT           2 + 1  6,2,8,8       opcode aop reg 0        reg
// "add"  + ADDRMD_2OP_INDIRECT_AUTO_INC = REG_WORD, AOP_INDIRECT_AUTO_INC  2 + 1  6,2,8,8       opcode aop reg 1        reg
// "add"  + ADDRMD_2OP_INDEXED           = REG_WORD, AOP_WORD_INDEXED       2 + 2  6,2,7,1,8,8   opcode aop reg 0 offset reg
// "add"  + ADDRMD_2OP_INDEXED_LONG      = REG_WORD, AOP_WORD_INDEXED_LONG  2 + 3  6,2,7,1,16,8  opcode aop reg 1 offset reg
// "djnz" + ADDRMD_2OP_CADD              = REG_BYTE, CADD
// "jbc"  + ADDRMD_3OP_JUMP_BIT          = REG_BYTE, BITNO, CADD
// "sh"   + ADDRMD_2OP_SHIFT_COUNT       = REG_BYTE, IMMEDIATE
// "sh"   + ADDRMD_2OP_SHIFT_REG         = REG_BYTE, REG_BYTE


/*
 * instruction operand formats
 *
 * OPFMT_INTRINSIC              mnem
 *
 * OPFMT_1OP_DIRECT             mnem        expr
 * OPFMT_1OP_IMMEDIATE          mnem        #expr
 * OPFMT_1OP_INDIRECT           mnem        [expr]
 * OPFMT_1OP_INDIRECT_AUTO_INC  mnem        [expr]+
 * OPFMT_1OP_INDEXED            mnem        expr[expr]
 *
 * OPFMT_2OP_DIRECT             mnem        expr, expr
 * OPFMT_2OP_IMMEDIATE          mnem        expr, #expr
 * OPFMT_2OP_INDIRECT           mnem        expr, [expr]
 * OPFMT_2OP_INDIRECT_AUTO_INC  mnem        expr, [expr]+
 * OPFMT_2OP_INDEXED            mnem        expr, expr[expr]
 *
 * OPFMT_3OP_DIRECT             mnem        expr, expr, expr
 * OPFMT_3OP_IMMEDIATE          mnem        expr, expr, #expr
 * OPFMT_3OP_INDIRECT           mnem        expr, expr, [expr]
 * OPFMT_3OP_INDIRECT_AUTO_INC  mnem        expr, expr, [expr]+
 * OPFMT_3OP_INDEXED            mnem        expr, expr, expr[expr]
 */
enum OPFMT
{
    OPFMT_INTRINSIC = 0,
    OPFMT_1OP_DIRECT,
    OPFMT_1OP_IMMEDIATE,
    OPFMT_1OP_INDIRECT,
    OPFMT_1OP_INDIRECT_AUTO_INC,
    OPFMT_1OP_INDEXED,
    OPFMT_2OP_DIRECT,
    OPFMT_2OP_IMMEDIATE,
    OPFMT_2OP_INDIRECT,
    OPFMT_2OP_INDIRECT_AUTO_INC,
    OPFMT_2OP_INDEXED,
    OPFMT_3OP_DIRECT,
    OPFMT_3OP_IMMEDIATE,
    OPFMT_3OP_INDIRECT,
    OPFMT_3OP_INDIRECT_AUTO_INC,
    OPFMT_3OP_INDEXED,
};


/*
 * operand type identifiers
 */
enum OPID
{
    OPID_DIRECT            = 'D', /* expression                    */
    OPID_IMMEDIATE         = 'I', /* '#' expression                */
    OPID_INDIRECT          = 'N', /* '[' expression ']'            */
    OPID_INDIRECT_AUTO_INC = 'A', /* '[' expression ']' '+'        */
    OPID_INDEXED_OFFSET    = 'X', /* expression '[' ---------- ']' */
    OPID_INDEXED_REGISTER  = 'Y', /* ---------- '[' expression ']' */
};


/*
 * instruction operand format definitions
 *
 * #define OPERAND_FORMAT_DEF(format, signature, operands, fields)
 */
#define OPERAND_FORMATS                                                        \
    OPERAND_FORMAT_DEF( OPFMT_INTRINSIC,             "@",     0, 0 ),          \
    OPERAND_FORMAT_DEF( OPFMT_1OP_DIRECT,            "@D",    1, 1 ),          \
    OPERAND_FORMAT_DEF( OPFMT_1OP_IMMEDIATE,         "@I",    1, 1 ),          \
    OPERAND_FORMAT_DEF( OPFMT_1OP_INDIRECT,          "@N",    1, 1 ),          \
    OPERAND_FORMAT_DEF( OPFMT_1OP_INDIRECT_AUTO_INC, "@A",    1, 1 ),          \
    OPERAND_FORMAT_DEF( OPFMT_1OP_INDEXED,           "@XY",   1, 2 ),          \
    OPERAND_FORMAT_DEF( OPFMT_2OP_DIRECT,            "@DD",   2, 2 ),          \
    OPERAND_FORMAT_DEF( OPFMT_2OP_IMMEDIATE,         "@DI",   2, 2 ),          \
    OPERAND_FORMAT_DEF( OPFMT_2OP_INDIRECT,          "@DN",   2, 2 ),          \
    OPERAND_FORMAT_DEF( OPFMT_2OP_INDIRECT_AUTO_INC, "@DA",   2, 2 ),          \
    OPERAND_FORMAT_DEF( OPFMT_2OP_INDEXED,           "@DXY",  2, 3 ),          \
    OPERAND_FORMAT_DEF( OPFMT_3OP_DIRECT,            "@DDD",  3, 3 ),          \
    OPERAND_FORMAT_DEF( OPFMT_3OP_IMMEDIATE,         "@DDI",  3, 3 ),          \
    OPERAND_FORMAT_DEF( OPFMT_3OP_INDIRECT,          "@DDN",  3, 3 ),          \
    OPERAND_FORMAT_DEF( OPFMT_3OP_INDIRECT_AUTO_INC, "@DDA",  3, 3 ),          \
    OPERAND_FORMAT_DEF( OPFMT_3OP_INDEXED,           "@DDXY", 3, 4 ),          \


// "add"  + ADDRMD_2OP_DIRECT            = REG_WORD, AOP_WORD_DIRECT        2 + 1  6,2,8,8       opcode aop reg          reg
// "add"  + ADDRMD_2OP_DIRECT_LONG       = REG_WORD, AOP_WORD_DIRECT_LONG   2 + 3  6,2,8,16,8    opcode aop 0   1 offset reg
// "add"  + ADDRMD_2OP_IMMEDIATE         = REG_WORD, AOP_WORD_IMMEDIATE     2 + 2  6,2,16,8
// "add"  + ADDRMD_2OP_INDIRECT          = REG_WORD, AOP_INDIRECT           2 + 1  6,2,8,8       opcode aop reg 0        reg
// "add"  + ADDRMD_2OP_INDIRECT_AUTO_INC = REG_WORD, AOP_INDIRECT_AUTO_INC  2 + 1  6,2,8,8       opcode aop reg 1        reg
// "add"  + ADDRMD_2OP_INDEXED           = REG_WORD, AOP_WORD_INDEXED       2 + 2  6,2,7,1,8,8   opcode aop reg 0 offset reg
// "add"  + ADDRMD_2OP_INDEXED_LONG      = REG_WORD, AOP_WORD_INDEXED_LONG  2 + 3  6,2,7,1,16,8  opcode aop reg 1 offset reg


/*
 * instruction addressing modes
 */
#define ADDRESSING_MODES                                                       \
    ADDRESSING_MODE( ADDRMD_INTRINSIC,             _BV(0), 0 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_DIRECT,            _BV(1), 1 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_DIRECT_LONG,       _BV(2), 3 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_IMMEDIATE,         _BV(3), 0 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_INDIRECT,          _BV(4), 1 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_INDIRECT_AUTO_INC, _BV(5), 1 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_INDEXED,           _BV(6), 2 ),                \
    ADDRESSING_MODE( ADDRMD_1OP_INDEXED_LONG,      _BV(7), 3 ),                \
    ADDRESSING_MODE( ADDRMD_2OP_DIRECT,            _BV(11), 1 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_DIRECT_LONG,       _BV(12), 3 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_IMMEDIATE,         _BV(13), 0 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_INDIRECT,          _BV(15), 1 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_INDIRECT_AUTO_INC, _BV(16), 1 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_INDEXED,           _BV(17), 2 ),               \
    ADDRESSING_MODE( ADDRMD_2OP_INDEXED_LONG,      _BV(18), 3 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_DIRECT,            _BV(22), 1 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_DIRECT_LONG,       _BV(23), 3 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_IMMEDIATE,         _BV(24), 0 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_INDIRECT,          _BV(26), 1 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_INDIRECT_AUTO_INC, _BV(27), 1 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_INDEXED,           _BV(28), 2 ),               \
    ADDRESSING_MODE( ADDRMD_3OP_INDEXED_LONG,      _BV(29), 3 ),               \


//ADDRESSING_MODE( ADDRMD_1OP_BYTE_IMMEDIATE,    _BV(2), 1 ),                \
//ADDRESSING_MODE( ADDRMD_1OP_WORD_IMMEDIATE,    _BV(3), 2 ),                \
//ADDRESSING_MODE( ADDRMD_1OP_CADD,              _BV(8), 0 ),                \
//ADDRESSING_MODE( ADDRMD_1OP_CADD_SHORT,        _BV(9), 0 ),                \
//ADDRESSING_MODE( ADDRMD_1OP_CADD_LONG,         _BV(10), 0 ),               \
//ADDRESSING_MODE( ADDRMD_2OP_BYTE_IMMEDIATE,    _BV(13), 1 ),               \
//ADDRESSING_MODE( ADDRMD_2OP_WORD_IMMEDIATE,    _BV(14), 2 ),               \
//ADDRESSING_MODE( ADDRMD_2OP_CADD,              _BV(19), 0 ),               \
//ADDRESSING_MODE( ADDRMD_2OP_CADD_SHORT,        _BV(20), 0 ),               \
//ADDRESSING_MODE( ADDRMD_2OP_CADD_LONG,         _BV(21), 0 ),               \
//ADDRESSING_MODE( ADDRMD_3OP_BYTE_IMMEDIATE,    _BV(24), 1 ),               \
//ADDRESSING_MODE( ADDRMD_3OP_WORD_IMMEDIATE,    _BV(25), 2 ),               \
//ADDRESSING_MODE( ADDRMD_3OP_CADD,              _BV(30), 0 ),               \
//ADDRESSING_MODE( ADDRMD_3OP_CADD_SHORT,        _BV(31), 0 ),               \
//ADDRESSING_MODE( ADDRMD_3OP_CADD_LONG,         _BV(32), 0 ),               \

#define ADDRESSING_MODE_
#define ADDR_MODE_
#define ADDRMODE_
#define ADRMODE_
#define ADMODE_
#define ADRMD_


#define ADDRESSING_MODE(symbol,value,bea) symbol=value
enum ADDRMD
{
    ADDRESSING_MODES
};
#undef ADDRESSING_MODE


/*
 * instruction addressing mode combinations
 */
#define ADDRMD_SHIFTS        ( ADDRMD_2OP_DIRECT | ADDRMD_2OP_IMMEDIATE )

void init_operand_formats(void);
YYSTYPE get_operand(YYSTYPE operand_list, int index);
u_int32_t get_operand_value(YYSTYPE operand_list, int index);
YYSTYPE get_operand_format(YYSTYPE operand_list);

#endif // _IOPERANDS_H
