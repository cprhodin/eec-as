#include "project.h"
#include "eec-as.tab.h"
#include "ibitfields.h"
#include "ioperands.h"
#include "memory.h"
#include "assemble.h"
#include "bitfield.h"

u_int32_t get_addressing_mode(YYSTYPE operand_list);


void set_location_bitfield(u_int32_t memory_address, u_int_t offset, u_int_t width, u_int32_t bitfield)
{
    set_bitfield(tgt_memory + memory_address, offset, width, bitfield);
}

int assemble_instruction(YYLTYPE * lloc, YYSTYPE mnemonic, YYSTYPE operand_list)
{
    struct source_line_desc * source_line;
    int memory_address;

    struct instr_bitfield const * bitfields;
    struct instruction_template * instr_tmpl;
    u_int32_t addr_mode;
    u_int_t offset;
    int index;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("%4d: %s", source_line->line_number, source_line->line);
        printf("\n\nFATAL ERROR: assemble_instruction invalid line number\n");
        exit(1);
    }

    memory_address = source_line->memory_address;

    // get the addressing mode from the operands
    if (!(addr_mode = get_addressing_mode(operand_list)))
    {
        printf("%4d: %s", source_line->line_number, source_line->line);
        printf("FATAL ERROR: invalid addressing mode\n\n");
        exit(1);
    }

    // find the assembly definition that matches the addressing mode
    list_for_each_entry(instr_tmpl, &mnemonic->obj_list, list)
    {
        if (instr_tmpl->addr_mode & addr_mode) break;

        if (instr_tmpl->list.next == &mnemonic->obj_list)
        {
            printf("%4d: %s", source_line->line_number, source_line->line);
            printf("\n\nFATAL ERROR: addressing mode not supported by instruction\n");
            exit(1);
            break;
        }
    }

    offset = 0;

    for (bitfields = instr_tmpl->bitfields; bitfields->type != IBF_END; bitfields++)
    {
        u_int32_t value = 0;

        switch (bitfields->type)
        {
        // instruction opcode
        case IBF_OPCODE:
            value = instr_tmpl->opcode;
            break;

        default:
            switch (bitfields->type >> 3)
            {
            // operand value
            case 0:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                break;
            // operand value mod 2
            case 1:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x1)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("FATAL ERROR: operand %d must be a multiple of 2\n", bitfields->type & 0x7);
                    exit(1);
                }
                value &= ~0x1;
                break;
            // operand value mod 4
            case 2:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x3)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("\n\nFATAL ERROR: operand must be a multiple of 4\n");
                    exit(1);
                }
                value &= ~0x3;
                break;
            // operand value mod 8
            case 3:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x3)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("\n\nFATAL ERROR: operand must be a multiple of 8\n");
                    exit(1);
                }
                value &= ~0x7;
                break;
            // constant value
            case 4:
                value = bitfields->type & 0x7;
                break;
            // operand value mod 2 and shift
            case 5:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x1)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("\n\nFATAL ERROR: operand %d must be a multiple of 2\n", bitfields->type & 0x7);
                    exit(1);
                }
                value >>= 1;
                break;
            // operand value mod 4 and shift
            case 6:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x3)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("\n\nFATAL ERROR: operand must be a multiple of 4\n");
                    exit(1);
                }
                value >>= 2;
                break;
            // operand value mod 8 and shift
            case 7:
                value = get_operand_value(operand_list, bitfields->type & 0x7);
                if (value & 0x7)
                {
                    printf("%4d: %s", source_line->line_number, source_line->line);
                    printf("\n\nFATAL ERROR: operand must be a multiple of 8\n");
                    exit(1);
                }
                value >>= 3;
                break;
            }
            break;
        }

        if (bitfields->width == 16) value = swap16(value);
        set_location_bitfield(memory_address, offset, bitfields->width, value);
        offset += bitfields->width;
    }

    if (offset % 8)
    {
        printf("%4d: %s", source_line->line_number, source_line->line);
        printf("\n\nFATAL ERROR: instruction bitfields not a multiple of 8 bits\n");
        exit(1);
    }

    source_line->memory_size = offset / 8;

    offset = 0;
    for (bitfields = instr_tmpl->bitfields; bitfields->type != IBF_END; bitfields++)
    {
        u_int32_t value = 0;

        if (bitfields->type == IBF_OP0_DISP)
        {
            value = get_operand_value(operand_list, 0) - (memory_address + source_line->memory_size);

            if (bitfields->width == 16) value = swap16(value);
            set_location_bitfield(memory_address, offset, bitfields->width, value);
        }

        if (bitfields->type == IBF_OP1_DISP)
        {
            value = get_operand_value(operand_list, 1) - (memory_address + source_line->memory_size);

            if (bitfields->width == 16) value = swap16(value);
            set_location_bitfield(memory_address, offset, bitfields->width, value);
        }

        if (bitfields->type == IBF_OP2_DISP)
        {
            value = get_operand_value(operand_list, 2) - (memory_address + source_line->memory_size);

            if (bitfields->width == 16) value = swap16(value);
            set_location_bitfield(memory_address, offset, bitfields->width, value);
        }
        offset += bitfields->width;
    }

    return source_line->memory_size;
}

int assemble_dcb(YYLTYPE * lloc, YYSTYPE expression_list)
{
    struct source_line_desc * source_line;
    int memory_address;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dcb invalid line number\n");
        exit(1);
    }

    memory_address = source_line->memory_address;

    if (expression_list)
    {
        YYSTYPE expression = expression_list;

        do
        {
            set_location_bitfield(memory_address, 0, 8, expression->value);
            memory_address += 1;

            expression = container_of(expression->obj_list.next, typeof(*expression), obj_list);
        }
        while (expression != expression_list);
    }

    return (source_line->memory_size = memory_address - source_line->memory_address);
}

int assemble_dcl(YYLTYPE * lloc, YYSTYPE expression_list)
{
    struct source_line_desc * source_line;
    int memory_address;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dcl invalid line number\n");
        exit(1);
    }

    memory_address = source_line->memory_address;

    if (expression_list)
    {
        YYSTYPE expression = expression_list;

        do
        {
            set_location_bitfield(memory_address, 0, 8, expression->value);
            set_location_bitfield(memory_address, 8, 8, expression->value >> 8);
            set_location_bitfield(memory_address, 16, 8, expression->value >> 16);
            set_location_bitfield(memory_address, 24, 8, expression->value >> 24);
            memory_address += 4;

            expression = container_of(expression->obj_list.next, typeof(*expression), obj_list);
        }
        while (expression != expression_list);
    }

    source_line->memory_size = memory_address - source_line->memory_address;

    return (source_line->memory_size = memory_address - source_line->memory_address);
}

int assemble_dcw(YYLTYPE * lloc, YYSTYPE expression_list)
{
    struct source_line_desc * source_line;
    int memory_address;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dcl invalid line number\n");
        exit(1);
    }

    memory_address = source_line->memory_address;

    if (expression_list)
    {
        YYSTYPE expression = expression_list;

        do
        {
            set_location_bitfield(memory_address, 0, 8, expression->value);
            set_location_bitfield(memory_address, 8, 8, expression->value >> 8);
            memory_address += 2;

            expression = container_of(expression->obj_list.next, typeof(*expression), obj_list);
        }
        while (expression != expression_list);
    }

    source_line->memory_size = memory_address - source_line->memory_address;

    return (source_line->memory_size = memory_address - source_line->memory_address);
}

int assemble_dsb(YYLTYPE * lloc, YYSTYPE expression)
{
    struct source_line_desc * source_line;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dsb invalid line number\n");
        exit(1);
    }

    printf(".dsw %d", expression->value);

    //location_counter->value += 1 * expression->value;

    printf("\n");
}

int assemble_dsl(YYLTYPE * lloc, YYSTYPE expression)
{
    struct source_line_desc * source_line;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dsl invalid line number\n");
        exit(1);
    }

    printf(".dsl %d", expression->value);

    //location_counter->value += 4 * expression->value;

    printf("\n");
}

int assemble_dsw(YYLTYPE * lloc, YYSTYPE expression)
{
    struct source_line_desc * source_line;

    if (!(source_line = find_source_line(lloc->first_line)))
    {
        printf("\n\nFATAL ERROR: assemble_dsw invalid line number\n");
        exit(1);
    }

    printf(".dsw %d", expression->value);

    //location_counter->value += 2 * expression->value;

    printf("\n");
}
