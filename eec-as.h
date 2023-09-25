#ifndef _EEC_AS_H
#define _EEC_AS_H

/*
 * available instruction set architectures
 */
enum isa_id
{
    ISA_MCS96,
    ISA_I8061,
    ISA_I8065,
};

struct isa
{
    enum isa_id id;
    char * name;
};

struct isa isa[] =
{
    { ISA_MCS96, "mcs-96" },
    { ISA_I8061, "i8061"  },
    { ISA_I8065, "i8065"  },
    { 0 }
};

/*
 * command line arguments
 */
struct arguments
{
    enum isa_id id; // Argument for -i
    int tabsize; // Argument for -T
    int debug; // Argument for -D
    struct list_head file_list; // arguments
};

struct file_argument
{
    struct list_head list;
    struct list_head file_list;
    int start_line;
    int lineno;
    int line;
    char * name;
};

extern struct arguments arguments;

#endif // _EEC_AS_H
