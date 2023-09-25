#include <stdio.h>
#include <stdlib.h>

#include "project.h"

#include "memory.h"

// 64K memory space
u_int8_t tgt_memory[0x10000];

extern FILE * hexfile;


void init_memory(void)
{
    memset(tgt_memory, 0xff, sizeof(tgt_memory));
}


// 0000000: 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20

void print_memory(void)
{
    u_int32_t address;

    for (address = 0; address < 0x10000;)
    {
        int i;
        fprintf(hexfile, "%08x:", address);

        for (i = 0; i < 16; i++)
        {
            fprintf(hexfile, " %02x", tgt_memory[address++]);
        }

        fprintf(hexfile, "\n");
    }
}


u_int32_t tgtbyte_read(u_int32_t tgt_addr)
{
    if (tgt_addr > 0x0000ffff)
    {
        fprintf(stderr, "\n\nFATAL ERROR: tgtbyte_read(), invalid address\n");
        exit(1);
    }

    return tgt_memory[tgt_addr];
}


void tgtbyte_write(u_int32_t tgt_addr, u_int32_t data)
{
    if (tgt_addr > 0x0000ffff)
    {
        fprintf(stderr, "\n\nFATAL ERROR: tgt_bytewrite(), invalid address\n");
        exit(1);
    }

    tgt_memory[tgt_addr] = (u_int8_t) data;
}


u_int32_t tgtbyte_read_modify_write(u_int32_t tgt_addr, u_int32_t and_mask, u_int32_t xor_mask)
{
    u_int32_t data;

    if (tgt_addr > 0x0000ffff)
    {
        fprintf(stderr, "\n\nFATAL ERROR: tgtbyte_read_modify_write(), invalid address\n");
        exit(1);
    }

    data = tgtbyte_read(tgt_addr);
    tgtbyte_write(tgt_addr, (data & and_mask) ^ xor_mask);

    return data;
}


u_int32_t tgtword_read(u_int32_t tgt_addr)
{
    if (tgt_addr > 0x0000fffe)
    {
        fprintf(stderr, "\n\nFATAL ERROR: tgtword_read(), invalid address\n");
        exit(1);
    }

    return tgt_memory[tgt_addr] | (tgt_memory[tgt_addr + 1] << 8);
}


void tgtword_write(u_int32_t tgt_addr, u_int32_t data)
{
    if (tgt_addr > 0x0000fffe)
    {
        fprintf(stderr, "\n\nFATAL ERROR: tgtword_write(), invalid address\n");
        exit(1);
    }

    tgt_memory[tgt_addr] = (u_int8_t) data;
    tgt_memory[tgt_addr + 1] = (u_int8_t) (data >> 8);
}
