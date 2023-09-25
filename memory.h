#ifndef _MEMORY_H
#define _MEMORY_H

extern u_int8_t tgt_memory[];

extern void init_memory(void);
extern void print_memory(void);

extern u_int32_t tgtbyte_read             (u_int32_t tgt_addr);
extern void      tgtbyte_write            (u_int32_t tgt_addr, u_int32_t data);
extern u_int32_t tgtbyte_read_modify_write(u_int32_t tgt_addr, u_int32_t and_mask, u_int32_t xor_mask);
extern u_int32_t tgtword_read             (u_int32_t tgt_addr);
extern void      tgtword_write            (u_int32_t tgt_addr, u_int32_t data);

#define tgtbyte_set_field(tgt_addr, field_mask, field_bits) tgtbyte_read_modify_write((tgt_addr), ~(field_mask), (field_mask) & (field_bits))

#endif // _MEMORY_H
