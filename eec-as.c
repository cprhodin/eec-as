#include "project.h"
#include "include_linux_list.h"

#include <argp.h>

#include "eec-as.h"

#include "eec-as.yy.h"

#include "eec-as.tab.h"
#include "ibitfields.h"
#include "ioperands.h"
#include "memory.h"
#include "assemble.h"
#include "i8061.h"


FILE * hexfile;
FILE * listfile;

const char *argp_program_version = "eec-as 1.0";

const char *argp_program_bug_address = "<cprhodin@gmail.com>";

//
// OPTIONS.  Field 1 in ARGP.
// Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
//
static struct argp_option options[] =
{
    {"debug",            'D', 0,         0, "Enable parser debug"},
    {"tabsize",          'T', "COLS",    0, "Assume tab stops at each COLS instead of 8"},
    {"hex-file",         'h', "NAME",    0, "Hex filename"},
    {"list-file",        'l', "NAME",    0, "List filename"},
    {"instruction-set",  'i', "ISA",     0, "Instruction set; mcs-96, i8061, i8065"},
    {0}
};

//
// PARSER. Field 2 in ARGP.
// Order of parameters: KEY, ARG, STATE.
//
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    struct file_argument * file_argument;

    switch (key)
    {
    case ARGP_KEY_INIT:
        /* initialize option arguments */
        arguments->id = ISA_MCS96;
        arguments->debug = 0;
        arguments->tabsize = 8;
        INIT_LIST_HEAD(&arguments->file_list);
        break;
    case 'D':
        arguments->debug = 1;
        break;
    case 'T':
        arguments->tabsize = strtol(arg, NULL, 0);
        break;
    case 'h':
        fclose(hexfile);
        hexfile = fopen(arg, "w");
        break;
    case 'l':
        fclose(listfile);
        listfile = fopen(arg, "w");
        break;
    case 'i':
        if (strncmp(arg, "mcs-96", 6) == 0)
            arguments->id = ISA_MCS96;
        else if (strncmp(arg, "i8061", 5) == 0)
            arguments->id = ISA_I8061;
        else if (strncmp(arg, "i8065", 5) == 0)
            arguments->id = ISA_I8065;
        break;
    case ARGP_KEY_ARG:
        file_argument = calloc_object(struct file_argument);
        file_argument->name = arg;
        list_add_tail(&file_argument->list, &arguments->file_list);
        break;
    case ARGP_KEY_END:
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

//
// ARGS_DOC. Field 3 in ARGP.
// A description of the non-option command-line arguments
//   that we accept.
//
static char args_doc[] = "";

//
//  DOC.  Field 4 in ARGP.
//  Program documentation.
//
static char doc[] =
"eec-as -- A program to assemble MCS-96 assembly language.";

//
// The ARGP structure itself.
//
static struct argp argp = { options, parse_opt, args_doc, doc };




struct instruction_inst
{
    u_int32_t opcode;
    char const * mnemonic;
    u_int32_t addr_mode;
    struct instr_bitfield const * bitfields;
};

//INSTRUCTION_INST( "skip",  0x00000000, flds_bytereg,    OPCODE_ROOT_8BIT,  OPFMT_1OP_DIRECT,       0 ),                                          \

#define INSTRUCTION_INST(mnemonic, opcode, bitfields, addr_mode, flags) opcode, mnemonic, addr_mode, bitfields
//
// prefixed instruction mnemonics
//
struct instruction_inst prefixed_instr_set_instance[] =
{
    I8061_PREFIXED_INSTRUCTION_SET
};
#define NUM_PREFIXED_INSTRUCTION (sizeof(prefixed_instr_set_instance) / sizeof(prefixed_instr_set_instance[0]))

//
// basic instruction mnemonics
//
struct instruction_inst instr_set_instance[] =
{
    I8061_INSTRUCTION_SET
};
#define NUM_INSTRUCTION (sizeof(instr_set_instance) / sizeof(instr_set_instance[0]))
#undef INSTRUCTION_INST

//
// addressing modes, strings preceded by an at sign "@" an otherwise illegal character
//
#define OPERAND_FORMAT_DEF(format, identifier, operands, fields) { identifier, format }
struct {
    char const * identifier;
    u_int32_t mode;
} addr_mode[] =
{
    OPERAND_FORMATS
};
#define NUM_ADDRESSING_MODE (sizeof(addr_mode) / sizeof(addr_mode[0]))
#undef OPERAND_FORMAT_DEF

//
// assembler directives
//
struct {
    char const * symbol;
    int type;
} assembler_directive[] =
{
    { ".dcb",       DCB    },
    { ".dcl",       DCL    },
    { ".dcw",       DCW    },
    { ".dsb",       DSB    },
    { ".dsl",       DSL    },
    { ".dsw",       DSW    },
    { ".else",      ELSE   },
    { ".elseif",    ELSEIF },
    { ".endif",     ENDIF  },
    { ".equ",       EQUATE },
    { ".if",        IF     },
    { ".include",   INCLUDE},
    { ".org",       ORIGIN },
    { ".set",       SET    },
};
#define NUM_ASSEMBLER_DIRECTIVE (sizeof(assembler_directive) / sizeof(assembler_directive[0]))


void add_template(struct instruction_inst const * i_inst)
{
    struct obj_desc * symbol;
    struct instruction_template * instr_tmpl;

    // silently return for instruction table entries that don't apply to this ISA
    if (!i_inst->mnemonic) return;

    // error if mnemonic is an empty string or first bitfield is not the opcode
    if ((*i_inst->mnemonic == '\0') || (i_inst->bitfields->type != IBF_OPCODE))
    {
        printf("\n\nFATAL ERROR: improperly formed instruction\n");
        exit(1);
    }

    // add the instruction mnemonic to the case-insensitive symbol table error on failure
    symbol = add_casesymbol(i_inst->mnemonic, MNEMONIC);
    if (!symbol)
    {
        printf("\n\nFATAL ERROR: failed to create instruction symbol\n");
        exit(1);
    }

    // check if addressing mode is already available
    list_for_each_entry(instr_tmpl, &symbol->obj_list, list)
        if (instr_tmpl->addr_mode == i_inst->addr_mode) return;

    // add new assembly definition
    instr_tmpl = calloc_object(struct instruction_template);
    INIT_LIST_HEAD(&instr_tmpl->list);

    instr_tmpl->opcode = i_inst->opcode >> (32 - i_inst->bitfields->width);
    instr_tmpl->addr_mode = i_inst->addr_mode;
    instr_tmpl->bitfields = i_inst->bitfields;

    list_add_tail(&instr_tmpl->list, &symbol->obj_list);
}


void crlf(void)
{
    putchar('\n');
}

u_int32_t puth(u_int32_t b)
{
    u_int32_t h = (b & 0xf) + 0x30;

    if (h > 0x39) h += 7;
    putchar(h);

    return h;
}

void puthex(u_int32_t val, u_int32_t dig)
{
    int shftcnt = dig * 4;

    do
    {
        shftcnt -= 4;
        puth(val >> shftcnt);
    } while (shftcnt != 0);
}

void dump(u_int32_t addr)
{
    int i;

    puthex((u_int32_t) addr, 4);
    for (i = 0; i < 16 ;i++) {
        putchar(' ');
        puthex(tgt_memory[addr++], 2);
    }
    crlf();
}


struct arguments arguments;

int main(int argc, char * argv[])
{
    struct instruction_inst * i_inst;
    struct file_argument * file_arg;
    struct obj_desc * symbol;
    int i;

    /*  */
    hexfile = fdopen(dup(STDOUT_FILENO), "w");
    listfile = fdopen(dup(STDOUT_FILENO), "w");

    /*
     * process command line options
     */

    /* call the options parser */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    tabsize = arguments.tabsize;
    yydebug = arguments.debug;

    init_memory();

    symbol_list_init();
    source_line_list_init();

    //
    // Insert instruction mnemonics into the case-insensitive symbol table.
    //
    for (i_inst = prefixed_instr_set_instance;
         i_inst < &prefixed_instr_set_instance[NUM_PREFIXED_INSTRUCTION];
         i_inst++)
        add_template(i_inst);

    for (i_inst = instr_set_instance;
         i_inst < &instr_set_instance[NUM_INSTRUCTION];
         i_inst++)
        add_template(i_inst);

    //
    // Insert assembler directives into the case-insensitive symbol table.
    //
    for (i = 0; i < NUM_ASSEMBLER_DIRECTIVE; i++)
    {
        symbol = add_casesymbol(assembler_directive[i].symbol, assembler_directive[i].type);
        if (symbol)
        {
            symbol->value = 0;
        }
    }

    /*
     * Insert operand format signaures into the case-insensitive symbol table.
     */
    init_operand_formats();

    //
    // Insert addressing mode strings into the case-insensitive symbol table.
    //
    for (i = 0; i < NUM_ADDRESSING_MODE; i++)
    {
        symbol = add_casesymbol(addr_mode[i].identifier, ADDRESSING_MODE);
        if (symbol)
        {
            symbol->value = addr_mode[i].mode;
        }
    }

    //
    // Insert the location counter symbol '$' into the case-insensitive symbol table.
    //
    location_counter = add_casesymbol("$", SYMBOL);
    location_counter->declared = 1;
    location_counter->defined = 1;
    location_counter->lvalue = 1;

    // default starting location is 0
    location_counter->value = 0;

    //
    // first pass
    //
    yyinitpass(1);
    list_for_each_entry(file_arg, &arguments.file_list, list)
    {
        YY_BUFFER_STATE current_buffer;
        FILE * current_file;
        int token;

//        printf("\nFile Name: %s\n", file_arg->name);

        if (!(current_file = fopen(file_arg->name, "r")))
        {
            printf("\n\nFATAL ERROR: could not open input file\n");
            exit(1);
        }
        yy_switch_to_buffer(current_buffer = yy_create_buffer(current_file, YY_BUF_SIZE));

//        do
//        {
//            token = yylex();
//            printf("token: %d\n", token);
//        }
//        while (token != END_OF_FILE);

        yyparse();

        yy_delete_buffer(current_buffer);
        fclose(current_file);
    }

    //
    // second pass
    //
    yyinitpass(2);
    yyparse();

/*
    dump(0x2000);
    dump(0x2010);
    dump(0x2020);
    dump(0x2030);
*/

//    for (i = 0; i < 0x25; i++)
//        printf("%02x\n", tgt_memory[0x2000 + i]);

//    print_mnemonic_list();
    print_source_line_list();
    print_symbol_list();
    print_memory();

    fclose(hexfile);
    fclose(listfile);

}
