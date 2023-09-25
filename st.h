#ifndef _ST_H_
#define _ST_H_

/*
 * defined indicates the value is valid and usable, forward references are undefined
 * lvalue indicates the value can be changed, labels and equates are not lvalues
 *
 * all fields are 0 unless explicitly used
 */

/*
 * assembly source code line
 *
 * FIELDS USED: type, value, string_length, string
 * NOT USED: declared, defined, lvalue, casei
 *
 *  type          = SOURCE_LINE
 *  value         = line number
 *  string_length = line length with newline and null
 *  string        = source line
 */

/*
 * subexpression result
 *
 * FIELDS USED: type, value, defined
 * NOT USED: declared, lvalue, casei, string_length, string
 *
 *  type          = SUBEXPRESSION_RESULT
 *  value         = subexpression value
 *  defined       = logical and of component defined's
 */

/*
 * object descriptor, one size fits all container
 */
struct obj_desc
{
    // object type
    int type;

    // object list
    struct list_head obj_list;

    // object value
    u_int32_t value;

    // flags
    u_int_t declared : 1; // set when symbol is first observed
    u_int_t defined : 1; // set if value has been assigned
    u_int_t lvalue : 1; // set if object is a legal lvalue
    u_int_t casei : 1; // case-insensitive string


    // flags
    u_int_t label : 1; // symbol is label
    u_int_t ro : 1; // object is read-only

    // strlen string size
    size_t string_length; // 0 if no string, allocation size is string_length + 1

    // null terminated string
    char string[0];
};

static inline struct obj_desc * alloc_obj_desc(size_t string_length)
{
    struct obj_desc * obj_desc;

    obj_desc = (struct obj_desc *) calloc(1, sizeof(struct obj_desc) + (string_length ? string_length + 1 : 0));
    if (obj_desc == NULL)
    {
        printf("\n\nFATAL ERROR: failed to allocate obj_desc object\n");
        exit(1);
    }

    INIT_LIST_HEAD(&obj_desc->obj_list);
    obj_desc->string_length = string_length;

    return obj_desc;
}


/*
 * symbol table lists
 */
extern void symbol_list_init(void);
extern struct obj_desc * find_symbol(char const * symbol);
extern struct obj_desc * add_casesymbol(char const * symbol, int type);
extern struct obj_desc * add_symbol(char const * symbol, int type);
extern void print_symbol_list(void);


/*
 * result descriptors
 */
extern YYSTYPE alloc_subx_result(u_int32_t value, int defined);
extern YYSTYPE realloc_subx_result(YYSTYPE subx_result);
extern void free_subx_result(YYSTYPE subx_result);


/*
 * source line descriptor
 */
struct source_line_desc
{
    // line number, based at 1
    int line_number;

    u_int32_t memory_address;
    u_int32_t memory_size;

    // strlen line size
    size_t line_length;

    // null terminated line, size is length + 1
    char * line;
};

static inline struct source_line_desc * alloc_source_line(void)
{
    struct source_line_desc * source_line_desc;

    source_line_desc = calloc_object(struct source_line_desc);
    if (source_line_desc == NULL)
    {
        printf("\n\nFATAL ERROR: failed to allocate source_line_desc object\n");
        exit(1);
    }

    return source_line_desc;
}


/*
 * source line lists
 */
extern void source_line_list_init(void);
extern struct source_line_desc * find_source_line(int line_number);
extern struct source_line_desc * add_source_line(int line_number);
extern char const * get_source_line(int line_number);
extern void print_source_line_list(void);

#endif // _ST_H_
