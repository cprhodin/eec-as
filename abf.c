

{  2, IBF_WORD_AOP },              // =0     this comes from the addressing mode
{  8, IBF_SRC_WORD_REGISTER },     //  op1

{  2, IBF_WORD_AOP },              // =0     this comes from the addressing mode
{  8, IBF_SRC_WORD_REGISTER },     //  op2

    ----

{  2, IBF_WORD_AOP },              // =1     this comes from the addressing mode
{ 16, IBF_IMMEDIATE },             //  op1

{  2, IBF_WORD_AOP },              // =1     this comes from the addressing mode
{ 16, IBF_IMMEDIATE },             //  op2

    ----

{  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op1
{  1, IBF_AOP_OPTION },            // =0     this comes from the addressing mode

{  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op2
{  1, IBF_AOP_OPTION },            // =0     this comes from the addressing mode

    ----

{  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op1
{  1, IBF_AOP_OPTION },            // =1     this comes from the addressing mode

{  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op2
{  1, IBF_AOP_OPTION },            // =1     this comes from the addressing mode

    ----

{  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op2
{  1, IBF_AOP_OPTION },            //  0
{  8, IBF_IMMEDIATE },             //  op1

{  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op3
{  1, IBF_AOP_OPTION },            //  0
{  8, IBF_IMMEDIATE },             //  op2

    ----

{  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op2
{  1, IBF_AOP_OPTION },            //  1
{ 16, IBF_IMMEDIATE },             //  op1

{  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
{  7, IBF_ADDRESS_REGISTER },      //  op3
{  1, IBF_AOP_OPTION },            //  1
{ 16, IBF_IMMEDIATE },             //  op2




struct instr_bitfield const add_2op_byte[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_BYTE_AOP },              //  *     this comes from the addressing mode
    {  8, IBF_DST_BYTE_REGISTER },     //  op0
    {  0, IBF_END }
};


struct instr_bitfield const add_2op_word[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              //  *     this comes from the addressing mode
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


struct instr_bitfield const add_3op_byte[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_BYTE_AOP },              //  *     this comes from the addressing mode
    {  8, IBF_SRC_BYTE_REGISTER },     //  op1
    {  8, IBF_DST_BYTE_REGISTER },     //  op0
    {  0, IBF_END }
};


struct instr_bitfield const add_3op_word[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              //  *     this comes from the addressing mode
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};




// bitfields for all forms of the "add" instruction
//
// = knowing the instruction and addressing mode
//


// "add op0, op1                          "@DD"

struct instr_bitfield const add_direct[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =0     this comes from the addressing mode
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, #op1                         "@DI"

struct instr_bitfield const add_immediate[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =1     this comes from the addressing mode
    { 16, IBF_IMMEDIATE },             //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, [op1]                        "@DN"

struct instr_bitfield const add_indirect[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op1
    {  1, IBF_AOP_OPTION },            // =0     this comes from the addressing mode
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, [op1]+                       "@DA"

struct instr_bitfield const add_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op1
    {  1, IBF_AOP_OPTION },            // =1     this comes from the addressing mode
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};



// "add op0, op1[op2]                     "@DXY"

struct instr_bitfield const add_indexed_short[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op2
    {  1, IBF_AOP_OPTION },            //  0
    {  8, IBF_IMMEDIATE },             //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1[op2]                     "@DXY"

struct instr_bitfield const add_indexed_long[] =
{
    {  6, IBF_OPCODE },                // =19    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op2
    {  1, IBF_AOP_OPTION },            //  1
    { 16, IBF_IMMEDIATE },             //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};



// "add op0, op1, op2                     "@DDD"

struct instr_bitfield const add_direct[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =0     this comes from the addressing mode
    {  8, IBF_SRC_WORD_REGISTER },     //  op2
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1, #op2                    "@DDI"

struct instr_bitfield const add_immediate[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =1     this comes from the addressing mode
    { 16, IBF_IMMEDIATE },             //  op2
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1, [op2]                   "@DDN"

struct instr_bitfield const add_indirect[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op2
    {  1, IBF_AOP_OPTION },            // =0     this comes from the addressing mode
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1, [op2]+                  "@DDA"

struct instr_bitfield const add_indirect_auto_inc[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =2     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op2
    {  1, IBF_AOP_OPTION },            // =1     this comes from the addressing mode
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1, op2[op3]                "@DDXY"

struct instr_bitfield const add_indexed_short[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op3
    {  1, IBF_AOP_OPTION },            //  0
    {  8, IBF_IMMEDIATE },             //  op2
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};


// "add op0, op1, op2[op3]                "@DDXY"

struct instr_bitfield const add_indexed_long[] =
{
    {  6, IBF_OPCODE },                // =11    this comes from the instruction symbol value
    {  2, IBF_WORD_AOP },              // =3     this comes from the addressing mode
    {  7, IBF_ADDRESS_REGISTER },      //  op3
    {  1, IBF_AOP_OPTION },            //  1
    { 16, IBF_IMMEDIATE },             //  op2
    {  8, IBF_SRC_WORD_REGISTER },     //  op1
    {  8, IBF_DST_WORD_REGISTER },     //  op0
    {  0, IBF_END }
};





