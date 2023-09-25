#ifndef _ASSEMBLE_H
#define _ASSEMBLE_H


struct instruction_template
{
    struct list_head list;
    struct instr_bitfield const * bitfields;
    u_int32_t addr_mode;
    u_int32_t opcode;
};


struct instruction_def {
    struct list_head list;
    struct instr_bitfield const * bitfields;
    u_int32_t opcode;
    u_int32_t mode;
};


extern int assemble_instruction(YYLTYPE * lloc, YYSTYPE mnemonic, YYSTYPE operand_list);
extern int assemble_dcb(YYLTYPE * lloc, YYSTYPE expression_list);
extern int assemble_dcl(YYLTYPE * lloc, YYSTYPE expression_list);
extern int assemble_dcw(YYLTYPE * lloc, YYSTYPE expression_list);
extern int assemble_dsb(YYLTYPE * lloc, YYSTYPE expression);
extern int assemble_dsl(YYLTYPE * lloc, YYSTYPE expression);
extern int assemble_dsw(YYLTYPE * lloc, YYSTYPE expression);

#endif // _ASSEMBLE_H
