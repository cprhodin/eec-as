#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "project.h"
#include "eec-as.tab.h"

#include <avl.h>

#include "include_linux_list.h"

#include "st.h"

u_int32_t tgtbyte_read(u_int32_t tgt_addr);


extern FILE * listfile;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ordered list of symbols
//
//  there are two symbol lists one for case-insensitive and one for case-sensitive symbols
//
//  case-insensitive symbols are the predefined instruction mnemonics and assembler directives
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//
// the symbol lists are stored in AVL Trees
//
avl_tree_t casesymbol_list; // case-insensitive symbols
avl_tree_t symbol_list; // case-sensitive symbols

static void free_symbol_list_entry(void * symbol_entry)
{
    printf("\n\nFATAL ERROR: tried to free a symbol_list_entry\n");
    exit(1);
}

static int compare_casesymbol_list_entry(const void * name1, const void * name2)
{
    return strcasecmp(name1, name2);
}

static int compare_symbol_list_entry(const void * name1, const void * name2)
{
    return strcmp(name1, name2);
}

void symbol_list_init(void)
{
    avl_init_tree(&casesymbol_list, compare_casesymbol_list_entry, free_symbol_list_entry);
    avl_init_tree(&symbol_list, compare_symbol_list_entry, free_symbol_list_entry);
}

struct obj_desc * find_symbol(char const * symbol)
{
    avl_node_t * avl_node;

    if ((symbol == NULL) || (*symbol == '\0'))
    {
        return NULL;
    }

    avl_node = avl_search(&casesymbol_list, symbol);
    if (avl_node == NULL)
        avl_node = avl_search(&symbol_list, symbol);

    if (avl_node == NULL)
        return NULL;

    return container_of(avl_node->item, struct obj_desc, string);
}

struct obj_desc * add_casesymbol(char const * symbol, int type)
{
    struct obj_desc * entry;

    if ((symbol == NULL) || (*symbol == '\0'))
    {
        return NULL;
    }

    entry = find_symbol(symbol);

    if (entry == NULL)
    {
        entry = alloc_obj_desc(strlen(symbol));
        entry->type = type;
        strcpy(entry->string, symbol);
        entry->casei = 1;

        avl_insert(&casesymbol_list, entry->string);
    }
    else
    {
        if (entry->casei == 0)
        {
            printf("\n\nFATAL ERROR: case-sensitive symbol already exists\n");
            exit(1);
        }
    }

    return entry;
}

struct obj_desc * add_symbol(char const * symbol, int type)
{
    struct obj_desc * entry;

    if ((symbol == NULL) || (*symbol == '\0'))
    {
        return NULL;
    }

    entry = find_symbol(symbol);

    if (entry == NULL)
    {
        entry = alloc_obj_desc(strlen(symbol));
        entry->type = type;
        strcpy(entry->string, symbol);

        avl_insert(&symbol_list, entry->string);
    }

    return entry;
}

void print_mnemonic_list(void)
{
    struct instruction_template * instr_tmpl;
    u_int_t idx;

    for (idx = 0;; idx++)
    {
        struct obj_desc * entry;
        avl_node_t * avl_node;

        avl_node = avl_at(&casesymbol_list, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct obj_desc, string);

        if (entry->type != MNEMONIC) continue;

        //
        // print symbol
        //
        printf("%s = %08x\n", entry->string, entry->value);

        list_for_each_entry(instr_tmpl, &entry->obj_list, list)
        {
            printf("    %08x %08x\n", instr_tmpl->addr_mode, instr_tmpl->opcode);
        }
    }
}

void print_symbol_list(void)
{
    u_int_t idx;

    for (idx = 0;; idx++)
    {
        struct obj_desc * entry;
        avl_node_t * avl_node;

        avl_node = avl_at(&symbol_list, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct obj_desc, string);

        //
        // print symbol
        //
        printf("%08x  %c  %s\n", entry->value, entry->defined ? 'D' : 'U', entry->string);
//        printf("%3d %c %s = %04x\n", entry->type, entry->defined ? 'D' : 'U', entry->string, entry->value);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ordered list of source lines
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//
// the source line list is stored in an AVL Tree
//
avl_tree_t source_line_list;

static void free_source_line_list_entry(void * source_line_list_entry)
{
    printf("\n\nFATAL ERROR: tried to free a source_line_list_entry\n");
    exit(1);
}

static int compare_source_line_list_entry(const void * line1, const void * line2)
{
    if (*((int *) line1) > *((int *) line2)) return 1;
    if (*((int *) line1) < *((int *) line2)) return -1;
    return 0;
}

void source_line_list_init(void)
{
    avl_init_tree(&source_line_list, compare_source_line_list_entry, free_source_line_list_entry);
}

struct source_line_desc * find_source_line(int line_number)
{
    avl_node_t * avl_node;

    avl_node = avl_search(&source_line_list, &line_number);

    if (avl_node == NULL)
        return NULL;

    return container_of(avl_node->item, struct source_line_desc, line_number);
}

struct source_line_desc * add_source_line(int line_number)
{
    struct source_line_desc * entry;

//    printf("add_source_line(%d)\n", line_number);

    entry = alloc_source_line();
    entry->line_number = line_number;

    avl_insert(&source_line_list, &entry->line_number);

    return entry;
}

char const * get_source_line(int line_number)
{
    struct source_line_desc * entry;

    entry = find_source_line(line_number);

    if (entry == NULL) return NULL;

    return entry->line;
}

void print_source_line_list(void)
{
    u_int_t idx;

    for (idx = 0;; idx++)
    {
        struct source_line_desc * entry;
        avl_node_t * avl_node;
        int i;

        avl_node = avl_at(&source_line_list, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct source_line_desc, line_number);

        //
        // print line
        //
        fprintf(listfile, "%4d: %04x  ", entry->line_number, entry->memory_address);
        for (i = 0; i < 8; i++)
        {
            if (i < entry->memory_size)
                fprintf(listfile, "%02x ", tgtbyte_read(entry->memory_address + i));
            else
                fprintf(listfile, "   ");
        }
        fprintf(listfile, " %s", entry->line);
    }
}


YYSTYPE alloc_subx_result(u_int32_t value, int defined)
{
    YYSTYPE subx_result;

    subx_result = alloc_obj_desc(0);

    subx_result->type = SUBEXPRESSION_RESULT;
    subx_result->value = value;
    subx_result->defined = defined;

    return subx_result;
}

YYSTYPE realloc_subx_result(YYSTYPE subx_result)
{
    if (subx_result->type == SUBEXPRESSION_RESULT)
    {
        INIT_LIST_HEAD(&subx_result->obj_list);
        return subx_result;
    }

    return alloc_subx_result(subx_result->value, subx_result->defined);
}

void free_subx_result(YYSTYPE subx_result)
{
    if (subx_result && (subx_result->type == SUBEXPRESSION_RESULT))
    {
        struct list_head * next = subx_result->obj_list.next;

        while (next != &subx_result->obj_list)
        {
            subx_result->obj_list.next = next->next;
            free(container_of(next, struct obj_desc, obj_list));
        }
        free(subx_result);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
