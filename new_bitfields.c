

        {  2, IBF_AOP },              // 0
        {  8, IBF_SRC_WREG },         // 0 - 255
        {  8, IBF_DST_WREG },         // 0 - 255

        add     exp, exp < 256


        {  2, IBF_AOP },              // 3
        {  7, IBF_WREG },             // 0
        {  1, IBF_LONG },             // 1
        { 16, IBF_LONG_OFFSET },      // word address of value
        {  8, IBF_DST_WREG },         // 0 - 255

        add     exp, exp > 255


        {  2, IBF_AOP },              // 1
        { 16, IBF_WORD_IMM },         // 16-bit value
        {  8, IBF_DST_WREG },         // 0 - 255

        add     exp, #exp





        add     r34, [r99]
        add     r34, [r99]+
        add     r34, 0x12[r99]
        add     r34, 0x1234[r99]


struct instr_bitfield const aop_direct[] =
{
    {  2, IBF_CONST_0 },
    {  8, IBF_REG },
};

struct instr_bitfield const aop_direct_long[] =
{
    {  2, IBF_CONST_3 },
    {  8, IBF_CONST_1 },
    { 16, IBF_OFFSET },
};







// variants for ADD 2 operand

struct instr_bitfield const short_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 0
    {  8, IBF_SRC_WREG },         // 0 - 255
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const long_direct[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 3
    {  7, IBF_WREG },             // 0
    {  1, IBF_LONG },             // 1
    { 16, IBF_LONG_OFFSET },      // word address of value
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const immediate[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 1
    { 16, IBF_WORD_IMM },         // 16-bit value
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const indirect[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 2
    {  7, IBF_WREG },             // index register 0 - 255
    {  1, IBF_INC },              // 0
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const indirect_inc[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 2
    {  7, IBF_WREG },             // index register 0 - 255
    {  1, IBF_INC },              // 1
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const short_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 3
    {  7, IBF_WREG },             // index register 0 - 254
    {  1, IBF_LONG },             // 0
    {  8, IBF_SHORT_OFFSET },     // 8-bit address offset
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};

struct instr_bitfield const long_indexed[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_AOP },              // 3
    {  7, IBF_WREG },             // index register 0 - 255
    {  1, IBF_LONG },             // 1
    { 16, IBF_LONG_OFFSET },      // 16-bit address offset
    {  8, IBF_DST_WREG },         // 0 - 255
    {  0, IBF_END }
};


