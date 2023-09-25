#include "project.h"
#include "include_linux_list.h"
#include "eec-as.tab.h"
#include "ioperands.h"

/*
 * operand formats are symbols preceded by an "@" sign
 */
#define OPERAND_FORMAT_DEF(format, signature, operands, fields) { signature, format }
struct {
    char const * signature;
    enum OPFMT format;
} operand_format[] =
{
    OPERAND_FORMATS
};
#define NUM_OPERAND_FORMAT (sizeof(operand_format) / sizeof(operand_format[0]))
#undef OPERAND_FORMAT_DEF

void init_operand_formats(void)
{
    struct obj_desc * symbol;
    int i;

    for (i = 0; i < NUM_OPERAND_FORMAT; i++)
    {
        symbol = add_casesymbol(operand_format[i].signature, OPERAND_FORMAT);
        if (symbol)
        {
            symbol->value = operand_format[i].format;
        }
        else
        {
            printf("\n\nFATAL ERROR: add_casesymbol failed\n");
            exit(1);
        }
    }
}


YYSTYPE get_operand(YYSTYPE operand_list, int index)
{
    if (operand_list)
    {
        YYSTYPE operand = operand_list;

        do
        {
            if (!index--) return operand;

            operand = container_of(operand->obj_list.next, typeof(*operand), obj_list);
        }
        while (operand != operand_list);
    }

    return NULL;
}


u_int32_t get_operand_value(YYSTYPE operand_list, int index)
{
    YYSTYPE operand;

    operand = get_operand(operand_list, index);

    return operand->value;
}


YYSTYPE get_operand_format(YYSTYPE operand_list)
{
    char operand_signature[MAX_FIELDS + 2]; /* + '@' + '\0' */
    YYSTYPE operand;
    int index;

    // build the operand signature
    operand_signature[0] = '@';

    for (index = 0; (index < MAX_FIELDS) && (operand = get_operand(operand_list, index));)
        operand_signature[++index] = operand->type;

    operand_signature[++index] = '\0';

    // lookup and return the operand format
    return find_symbol(operand_signature);
}


u_int32_t get_addressing_mode(YYSTYPE operand_list)
{
    YYSTYPE operand_format;
    YYSTYPE operand;
    u_int32_t value;
    u_int32_t modes;

    if (!(operand_format = get_operand_format(operand_list)))
    {
        return 0;
    }

    modes = 0;
    switch (operand_format->value)
    {
    case OPFMT_INTRINSIC:
        modes |= ADDRMD_INTRINSIC;
        break;

    case OPFMT_1OP_DIRECT:
        operand = get_operand(operand_list, 0);
        modes |= ADDRMD_1OP_DIRECT_LONG;
        if (inrange(0, operand, 255)) modes |= ADDRMD_1OP_DIRECT;
        break;
    case OPFMT_1OP_IMMEDIATE:
        modes |= ADDRMD_1OP_IMMEDIATE;
        break;
    case OPFMT_1OP_INDIRECT:
        modes |= ADDRMD_1OP_INDIRECT;
        break;
    case OPFMT_1OP_INDIRECT_AUTO_INC:
        modes |= ADDRMD_1OP_INDIRECT_AUTO_INC;
        break;
    case OPFMT_1OP_INDEXED:
        operand = get_operand(operand_list, 0);
        modes |= ADDRMD_1OP_INDEXED_LONG;
        if (inrange(-128, operand, 127)) modes |= ADDRMD_1OP_INDEXED;
        break;

    case OPFMT_2OP_DIRECT:
        operand = get_operand(operand_list, 1);
        modes |= ADDRMD_2OP_DIRECT_LONG;
        if (inrange(0, operand, 255)) modes |= ADDRMD_2OP_DIRECT;
        break;
    case OPFMT_2OP_IMMEDIATE:
        modes |= ADDRMD_2OP_IMMEDIATE;
        break;
    case OPFMT_2OP_INDIRECT:
        modes |= ADDRMD_2OP_INDIRECT;
        break;
    case OPFMT_2OP_INDIRECT_AUTO_INC:
        modes |= ADDRMD_2OP_INDIRECT_AUTO_INC;
        break;
    case OPFMT_2OP_INDEXED:
        operand = get_operand(operand_list, 1);
        modes |= ADDRMD_2OP_INDEXED_LONG;
        if (inrange(-128, operand, 127)) modes |= ADDRMD_2OP_INDEXED;
        break;

    case OPFMT_3OP_DIRECT:
        operand = get_operand(operand_list, 2);
        modes |= ADDRMD_3OP_DIRECT_LONG;
        if (inrange(0, operand, 255)) modes |= ADDRMD_3OP_DIRECT;
        break;
    case OPFMT_3OP_IMMEDIATE:
        modes |= ADDRMD_3OP_IMMEDIATE;
        break;
    case OPFMT_3OP_INDIRECT:
        modes |= ADDRMD_3OP_INDIRECT;
        break;
    case OPFMT_3OP_INDIRECT_AUTO_INC:
        modes |= ADDRMD_3OP_INDIRECT_AUTO_INC;
        break;
    case OPFMT_3OP_INDEXED:
        operand = get_operand(operand_list, 2);
        modes |= ADDRMD_3OP_INDEXED_LONG;
        if (inrange(-128, operand, 127)) modes |= ADDRMD_3OP_INDEXED;
        break;
    }

    return modes;
}
