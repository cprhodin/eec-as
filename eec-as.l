%option noyywrap nodefault

%{
#include "project.h"
#include "eec-as.tab.h"

static int process_eof(void);
static void user_init(void);
static int expand_tab(char * dst, int column);
static void user_action(int yy_act);
static void alloc_src_buffer(size_t size);

static struct source_line_desc * lexer_source_line;

static char * src_buffer;
static char * src_buffer_ins;

#define COLUMN (src_buffer_ins - src_buffer)
#define YYCOLUMN (COLUMN + 1)

#define YY_USER_INIT user_init();
#define YY_USER_ACTION user_action(yy_act);
%}


D       [0-9]
L       [a-zA-Z_]
H       [a-fA-F0-9]
DL      {D}|{L}
C       {L}{DL}*


%% /***************************************************************************/


                    /*
                     * Discard comments.
                     */
";".*/"\n"          { }

                    /*
                     * Quoted string.  Filenames are the only example of this.
                     */
"\"".*"\""          {
                        yylval = alloc_obj_desc(yyleng - 2);
                        yylval->type = STRING_CONSTANT;
                        memcpy(yylval->string, yytext + 1, yyleng - 2);

                        return yylval->type;
                    }

                    /*
                     * Octal, decimal, and hexadecimal numeric constants.
                     */
0[xX]{H}+           |
0[0-7]*             |
[1-9]{D}*           {
                        yylval = alloc_subx_result(strtol(yytext, NULL, 0), 1);

                        return CONSTANT;
                    }

                    /*
                     * Built-in register names (r0, R0, r1, R1, ...).
                     */
[rR]{D}+            {
                        yylval =
                             alloc_subx_result(strtol(yytext + 1, NULL, 0), 1);

                        return CONSTANT;
                    }

                    /*
                     * The predefined assembler directives are preceded by a
                     * period and instructions are allowed to have embedded
                     * periods.
                     */
\.{C}               |
{C}\.({DL}|\.)*     {
                        yylval = add_symbol(yytext, ILLEGAL_SYMBOL);

                        return yylval->type;
                    }

                    /*
                     * All user defined symbols are C compatible.
                     */
{C}                 {
                        yylval = add_symbol(yytext, SYMBOL);

                        return yylval->type;
                    }

                    /*
                     * Relevant multi-character operators.
                     */
">>="               { return RIGHT_ASSIGN; }
"<<="               { return LEFT_ASSIGN; }
"+="                { return ADD_ASSIGN; }
"-="                { return SUB_ASSIGN; }
"*="                { return MUL_ASSIGN; }
"/="                { return DIV_ASSIGN; }
"%="                { return MOD_ASSIGN; }
"&="                { return AND_ASSIGN; }
"^="                { return XOR_ASSIGN; }
"|="                { return OR_ASSIGN; }
">>"                { return RIGHT_OP; }
"<<"                { return LEFT_OP; }
"++"                { return INC_OP; }
"--"                { return DEC_OP; }
"&&"                { return AND_OP; }
"||"                { return OR_OP; }
"<="                { return LE_OP; }
">="                { return GE_OP; }
"=="                { return EQ_OP; }
"!="                { return NE_OP; }

                    /*
                     * Location counter.
                     */
"$"                 {
                        yylval = location_counter;

                        return yylval->type;
                    }

                    /*
                     * Newline.
                     */
[ \t]*"\n"          { return NEWLINE; }

                    /*
                     * Whitespace.
                     */
" "*                |
"\t"                { }

                    /*
                     * Forward all remaining characters one at a time to the
                     * parser.
                     */
.                   { return *yytext; }

<<EOF>>             {
                        /*
                         * if actual end-of-file or end-of-pass let the parser
                         * handle it
                         */
                        if (process_eof())
                        {
                            return END_OF_FILE;
                        }
                    }


%% /***************************************************************************/


static void user_init(void)
{
    if (!yypassno || !yylineno)
    {
        printf("\n\nFATAL ERROR: illegal pass or line number\n");
        exit(1);
    }

    alloc_src_buffer(YY_BUF_SIZE);

    lexer_source_line = NULL;
}


static void alloc_src_buffer(size_t size)
{
    src_buffer = (char *) calloc(1, size);

    if (!src_buffer)
    {
        printf("\n\nFATAL ERROR: failed to allocate src_buffer\n");
        exit(1);
    }

    src_buffer_ins = src_buffer;
}


static int expand_tab(char * dst, int column)
{
    int length;

    length = tabsize - column % tabsize;
    memset(dst, ' ', length);

    return length;
}


/*
 * called before the action code for all rules except <<EOF>>
 */
static void user_action(int yy_act)
{
    char * yytext_end = yytext + yyleng;

//    printf("user_action(%d)\n", yy_act);

    yylloc.first_line = yylineno;
    yylloc.first_column = YYCOLUMN;

    if (yypassno == 1)
    {
        if (!lexer_source_line)
        {
            lexer_source_line = add_source_line(yylineno);

            lexer_source_line->line = src_buffer_ins = src_buffer;
            lexer_source_line->memory_address = location_counter->value;
        }
        else if (lexer_source_line->line_number != yylineno)
        {
            printf("\n\nFATAL ERROR: line number bad\n");
            exit(1);
        }

        if (*(yytext_end - 1) == '\n')
        {
//            printf("EOL: %d\n", yylineno);

            *src_buffer_ins++ = '\n';
            *src_buffer_ins = '\0';

            lexer_source_line->line = strdup(lexer_source_line->line);
            lexer_source_line->line_length = strlen(lexer_source_line->line);

            lexer_source_line = NULL;
            src_buffer_ins = src_buffer;
            yylineno++;
        }
        else if (*yytext == '\t')
        {
            src_buffer_ins += expand_tab(src_buffer_ins, COLUMN);
        }
        else if (*yytext == ';')
        {
            char * pc;

            for (pc = yytext; pc < yytext_end; pc++)
            {
                if (*pc == '\t')
                    src_buffer_ins += expand_tab(src_buffer_ins, COLUMN);
                else
                    *src_buffer_ins++ = *pc;
            }

            while (*(--src_buffer_ins) == ' ');
            src_buffer_ins++;
        }
        else
        {
            memcpy(src_buffer_ins, yytext, yyleng);

            src_buffer_ins += yyleng;
        }

        *src_buffer_ins = '\0';
    }
    else
    {
        if (*(yytext_end - 1) == '\n')
        {
            lexer_source_line = NULL;
            src_buffer_ins = src_buffer;
            yylineno++;
        }
        else
        {
            src_buffer_ins += yyleng;
        }
    }

    yylloc.last_line = yylineno;
    yylloc.last_column = YYCOLUMN;
}


/*
 * first pass processes and saves the input, all subsequent passes replay
 * the saved input
 */

static int process_eof(void)
{
//    printf("Pass %d, Line %d, Column %d, Buffer %08x\n", yypassno, yylineno,
//           YYCOLUMN, YY_CURRENT_BUFFER);

    if (yypassno == 1)
    {
        /*
         * append a new line to any file that doesn't end on column 1
         */
        static YY_BUFFER_STATE yy_buffer_state = NULL;

//        printf("yy_buffer_state: %08x\n", yy_buffer_state);

        if (YYCOLUMN != 1)
        {
            if (yy_buffer_state)
            {
                printf("\n\nFATAL ERROR: appending a newline failed\n");
                exit(1);
            }

            yy_buffer_state = YY_CURRENT_BUFFER;
            yy_scan_string("\n");
        }
        else
        {
            if (yy_buffer_state)
            {
                yy_delete_buffer(YY_CURRENT_BUFFER);
                yy_switch_to_buffer(yy_buffer_state);
                yy_buffer_state = NULL;
            }

            return 1;
        }
    }
    else
    {
        /*
         * play back the saved input one line at a time
         */
        size_t line_length;

        yy_delete_buffer(YY_CURRENT_BUFFER);

        lexer_source_line = find_source_line(yylineno);

        if (!lexer_source_line)
        {
            return 1;
        }

        line_length = lexer_source_line->line_length;

        memcpy(src_buffer, lexer_source_line->line, line_length);
        *(src_buffer + line_length) = YY_END_OF_BUFFER_CHAR;
        *(src_buffer + line_length + 1) = YY_END_OF_BUFFER_CHAR;

        yy_scan_buffer(src_buffer, line_length + 2);

        src_buffer_ins = src_buffer;
    }

    return 0;
}
