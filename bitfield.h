#ifndef _BITFIELD_H
#define _BITFIELD_H

extern u_int32_t get_bitfield(u_int8_t * address, u_int_t offset, u_int_t width);
extern void set_bitfield(u_int8_t * address, u_int_t offset, u_int_t width, u_int32_t bitfield);

#endif // _BITFIELD_H
