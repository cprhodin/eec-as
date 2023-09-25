%defines
%locations

%code top {
    /*
     * %code top { }                                                     *.tab.c
     */

    #define assert_is_lvalue(a) do {} while(0)
    #define desc_is_defined(a) do {} while(0)
    #define assert_not_defined(a) do {} while(0)
    #define desc_not_ro(a) do {} while(0)
}

%{
    /*
     * %{ %}                                                             *.tab.c
     */

    #include "project.h"
    #include "eec-as.yy.h"
%}

%code requires {
    /*
     * %code requires { }                                        *.tab.h *.tab.c
     */

    #include "include_linux_list.h"

    #include "ibitfields.h"
    #include "ioperands.h"

    #include "st.h"

    extern YYSTYPE location_counter;

    extern int yypassno;
    extern int tabsize;
}

%code provides {
    /*
     * %code provides { }                                        *.tab.h *.tab.c
     */

    #include "assemble.h"

    static inline void __list_merge(struct list_head * list_a,
                                    struct list_head * list_b)
    {
        struct list_head * head_a = list_a;
        struct list_head * tail_a = list_a->prev;
        struct list_head * head_b = list_b;
        struct list_head * tail_b = list_b->prev;

        head_a->prev = tail_b;
        tail_b->next = head_a;

        head_b->prev = tail_a;
        tail_a->next = head_b;
    }

    void yyinitpass(int passno);
    void yyerror(char *s);
}

%code {
    /*
     * %code { }                                                         *.tab.c
     */

    YYSTYPE location_counter;

    int yypassno;
    int tabsize;
    int file_depth = 0;
}


/*
 * Instruction mnemonics.
 */
%token MNEMONIC

/*
 * Assembler directives.
 */
%token DCB DCL DCW DSB DSL DSW ELSE ELSEIF ENDIF EQUATE IF INCLUDE ORIGIN SET

/*
 * Legal symbols that are not mnemonics or directives.
 */
%token SYMBOL

/*
 * Lexer detected illegal symbols.
 */
%token ILLEGAL_SYMBOL

/*
 * Quoted string with quotes removed (include directive filename).
 */
%token STRING_CONSTANT

/*
 * Lexer detected end of file.
 */
%token END_OF_FILE

/*
 * Numeric constants.
 */
%token CONSTANT

/*
 * Multi-character operators.
 */
%token RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN RIGHT_OP LEFT_OP INC_OP DEC_OP
%token AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP

/*
 * End of line.
 */
%token NEWLINE

/*
 * Reserve a token to represent subexpression results.
 */
%token SUBEXPRESSION_RESULT

/*
 * Reserve a token for instruction operand format signatures in the symbol
 * table.
 */
%token OPERAND_FORMAT

/*
 * Reserve a token for addressing mode entries in the symbol table.
 */
%token ADDRESSING_MODE


%%


assembly_unit
    : statements
    ;

statements
    : /* empty */
    | statements statement
    ;

statement
    : NEWLINE
    | INCLUDE STRING_CONSTANT NEWLINE
        {
            if (yypassno == 1)
            {
                YY_BUFFER_STATE bs;
                FILE * f;
                f = fopen($2->string, "r");
                if (!f)
                {
                    printf("\n\nFATAL ERROR: could not open include file.\n");
                    exit(1);
                }
                bs = yy_create_buffer(f, YY_BUF_SIZE);

                file_depth++;
                yypush_buffer_state(bs);
                //printf("yypush_buffer_state\n");
            }
        }
    | END_OF_FILE
        {
            if (file_depth)
            {
                file_depth--;
                yypop_buffer_state();
                //printf("yypop_buffer_state\n");
            }
            else
            {
                YYACCEPT;
            }
        }
    | label NEWLINE
    | instruction NEWLINE
        {
//            printf("%s", find_source_line(@$.first_line)->line);
        }
    | label instruction NEWLINE
        {
//            printf("%s", find_source_line(@$.first_line)->line);
        }
    | origin NEWLINE
    | equate NEWLINE
    | set NEWLINE
    | define_code NEWLINE
    | label define_code NEWLINE
    | define_storage NEWLINE
    | label define_storage NEWLINE
    | conditional_assembly NEWLINE
    | expression NEWLINE
        {
            free_subx_result($1);
        }
    ;

conditional_assembly
    : ELSE
    | ELSEIF expression
        {
            free_subx_result($2);
        }
    | ENDIF
    | IF expression
        {
            free_subx_result($2);
        }
    ;

    /*
     * A label is a read-only symbol.
     */
label
    : SYMBOL ':'
        {
            assert_not_defined($1);
            $1->value = location_counter->value;
            $1->defined = 1;
            $1->label = 1;
            $1->ro = 1;
        }
    ;

    /*
     * Origin sets the current location counter.
     */
origin
    : ORIGIN expression
        {
            location_counter->value = $2->value;
            free_subx_result($2);
        }
    ;

    /*
     * Equate defines a read-only symbol.
     */
equate
    : SYMBOL EQUATE expression
        {
            //printf("Equate\n");

            assert_not_defined($1);
            $1->value = $3->value;
            $1->defined = 1;
            $1->ro = 1;
            free_subx_result($3);
        }
    ;

    /*
     * Set defines or modifies a writable symbol.
     */
set
    : SYMBOL SET expression
        {
            desc_not_ro($1);
            $1->value = $3->value;
            $1->defined = 1;
            free_subx_result($3);
        }
    ;

define_code
    : DCB expression_list
        {
            location_counter->value += assemble_dcb(&@$, $2);
            free_subx_result($2);
        }
    | DCL expression_list
        {
            location_counter->value += assemble_dcl(&@$, $2);
            free_subx_result($2);
        }
    | DCW expression_list
        {
            location_counter->value += assemble_dcw(&@$, $2);
            free_subx_result($2);
        }
    ;

define_storage
    : DSB expression
        {
            location_counter->value += assemble_dsb(&@$, $2);
            free_subx_result($2);
        }
    | DSL expression
        {
            location_counter->value += assemble_dsl(&@$, $2);
            free_subx_result($2);
        }
    | DSW expression
        {
            location_counter->value += assemble_dsw(&@$, $2);
            free_subx_result($2);
        }
    ;

    /*
     * Assembly language instructions with zero or more operands.
     */
instruction
    : MNEMONIC operand_list
        {
            location_counter->value += assemble_instruction(&@$, $1, $2);
            free_subx_result($2);
        }
    ;

    /*
     * Instruction operands.
     */
operand_list
    : /* empty */
        {
            $$ = NULL;
        }
    | operand
        {
            $$ = $1;
        }
    | operand_list ',' operand
        {
            $$ = $1;

            __list_merge(&$$->obj_list, &$3->obj_list);
        }
    ;

operand
    : expression
        {
            $$ = realloc_subx_result($1);
            $$->type = OPID_DIRECT;
        }
    | '#' expression
        {
            $$ = realloc_subx_result($2);
            $$->type = OPID_IMMEDIATE;
        }
    | '[' expression ']'
        {
            $$ = realloc_subx_result($2);
            $$->type = OPID_INDIRECT;
        }
    | '[' expression ']' '+'
        {
            $$ = realloc_subx_result($2);
            $$->type = OPID_INDIRECT_AUTO_INC;
        }
    | expression '[' expression ']'
        {
            $$ = realloc_subx_result($1);
            $$->type = OPID_INDEXED_OFFSET;

            $3 = realloc_subx_result($3);
            $3->type = OPID_INDEXED_REGISTER;

            __list_merge(&$$->obj_list, &$3->obj_list);
        }
    ;

    /*
     * Directive operands.
     */
expression_list
    : expression
        {
            $$ = realloc_subx_result($1);
            $$->type = OPID_DIRECT;
        }
    | expression_list ',' expression
        {
            $$ = $1;

            $3 = realloc_subx_result($3);
            $3->type = 'D';

            __list_merge(&$$->obj_list, &$3->obj_list);
        }
    ;

    /*
     * C like expression processing.
     */
primary_expression
    : CONSTANT
    | SYMBOL
    | '(' expression ')'
        {
            $$ = realloc_subx_result($2);
        }
    ;

postfix_expression
    : primary_expression
    | postfix_expression INC_OP
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result(($1->value)++, $1->defined);
        }
    | postfix_expression DEC_OP
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result(($1->value)--, $1->defined);
        }
    ;

unary_expression
    : postfix_expression
    | INC_OP unary_expression
        {
            assert_is_lvalue($2);
            $$ = alloc_subx_result(++($2->value), $2->defined);
        }
    | DEC_OP unary_expression
        {
            assert_is_lvalue($2);
            $$ = alloc_subx_result(--($2->value), $2->defined);
        }
    | '+' unary_expression
        {
            $$ = realloc_subx_result($2);
        }
    | '-' unary_expression
        {
            $$ = realloc_subx_result($2);
            $$->value = -$$->value;
        }
    | '~' unary_expression
        {
            $$ = realloc_subx_result($2);
            $$->value = ~$$->value;
        }
    | '!' unary_expression
        {
            $$ = realloc_subx_result($2);
            $$->value = !$$->value;
        }
    ;

multiplicative_expression
    : unary_expression
    | multiplicative_expression '*' unary_expression
        {
            $$ = realloc_subx_result($1);
            $$->value *= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | multiplicative_expression '/' unary_expression
        {
            $$ = realloc_subx_result($1);
            $$->value /= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | multiplicative_expression '%' unary_expression
        {
            $$ = realloc_subx_result($1);
            $$->value %= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

additive_expression
    : multiplicative_expression
    | additive_expression '+' multiplicative_expression
        {
            $$ = realloc_subx_result($1);
            $$->value += $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | additive_expression '-' multiplicative_expression
        {
            $$ = realloc_subx_result($1);
            $$->value -= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

shift_expression
    : additive_expression
    | shift_expression LEFT_OP additive_expression
        {
            $$ = realloc_subx_result($1);
            $$->value <<= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | shift_expression RIGHT_OP additive_expression
        {
            $$ = realloc_subx_result($1);
            $$->value >>= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

relational_expression
    : shift_expression
    | relational_expression '<' shift_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value < $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | relational_expression '>' shift_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value > $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | relational_expression LE_OP shift_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value <= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | relational_expression GE_OP shift_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value >= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value == $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    | equality_expression NE_OP relational_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value != $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

and_expression
    : equality_expression
    | and_expression '&' equality_expression
        {
            $$ = realloc_subx_result($1);
            $$->value &= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression '^' and_expression
        {
            $$ = realloc_subx_result($1);
            $$->value ^= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression '|' exclusive_or_expression
        {
            $$ = realloc_subx_result($1);
            $$->value |= $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value && $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
        {
            $$ = realloc_subx_result($1);
            $$->value = $$->value || $3->value;
            $$->defined &= $3->defined;
            free_subx_result($3);
        }
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression '?' expression ':' conditional_expression
        {
            $$ = realloc_subx_result($1);
            if ($$->value)
            {
                $$->value = $3->value;
                $$->defined &= $3->defined;
            }
            else
            {
                $$->value = $5->value;
                $$->defined &= $5->defined;
            }
            free_subx_result($3);
            free_subx_result($5);
        }
    ;

expression
    : conditional_expression
    | unary_expression '=' expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value = $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression MUL_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value *= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression DIV_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value /= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression MOD_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value %= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression ADD_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value += $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression SUB_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value -= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression LEFT_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value <<= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression RIGHT_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value >>= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression AND_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value &= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression XOR_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value ^= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    | unary_expression OR_ASSIGN expression
        {
            assert_is_lvalue($1);
            $$ = alloc_subx_result($1->value |= $3->value,
                                   $1->defined &= $3->defined);
            free_subx_result($3);
        }
    ;


%%


void yyinitpass(int passno)
{
    yylineno = 1;
    yypassno = passno;

    /*
     * this will cause an EOF on entry to the lexer for all passes but 1
     */
    if (passno > 1) yy_scan_string("");
}


void yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}
