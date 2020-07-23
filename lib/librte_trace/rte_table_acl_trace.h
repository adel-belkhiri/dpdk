#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_acl

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_acl_trace.h"

#if !defined(_RTE_TABLE_ACL_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_ACL_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_acl.h>
#include <rte_table_acl.h>

#define MAX_BURST_PKT_NUM          64

/** 
 * Create an ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_create,
    TP_ARGS(
        const void*, tbl,
        const char*, name,
        uint32_t, name_id,
        struct rte_acl_param*, params,
        struct rte_acl_config*, cfg,
        uint32_t, entry_size
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_string(name, name)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_integer(int, socket_id, params->socket_id)
        ctf_integer(uint32_t, max_rule_num, params->max_rule_num)
        ctf_integer(uint32_t, rule_size, params->rule_size)
        ctf_integer(uint32_t, n_rule_fields, cfg->num_fields)
        ctf_integer(uint32_t, num_categories, cfg->num_categories)
        ctf_integer(size_t, mem_max_size, cfg->max_size)
        ctf_integer(uint32_t, entry_size, entry_size)

        ctf_sequence(uint32_t, field_def_type,
        ({
            uint32_t array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < cfg->num_fields; i++)
                array[i] = (uint32_t) cfg->defs[i].type;
            array;
        }), size_t, cfg->num_fields)

        ctf_sequence(uint32_t, field_def_size,
        ({
            uint32_t array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < cfg->num_fields; i++)
                array[i] = (uint32_t) cfg->defs[i].size;
            array;
        }), size_t, cfg->num_fields)        
    )
)

/** 
 * Delete an ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_free,
    TP_ARGS(
        const void*, tbl
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
    )
)

/** 
 * Add an entry to an ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_entry_add,
    TP_ARGS(
        const void*, tbl,
        uint32_t, name_id,
        uint32_t, num_fields,
        struct rte_table_acl_rule_add_params *, rule,
        uint32_t, rule_pos,
        const void*, entry_ptr,
        int, key_found,
        const void*, ctx
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_integer(int32_t, priority, rule->priority)

        ctf_sequence(uint32_t, field_value,
        ({
            uint32_t tmp_array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < num_fields; i++)
                tmp_array[i] = (uint32_t) rule->field_value[i].value.u32;
            tmp_array;
        }), size_t, num_fields)

        ctf_sequence(uint32_t, field_mask,
        ({
            uint32_t tmp_array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < num_fields; i++)
                tmp_array[i] = (uint32_t) rule->field_value[i].mask_range.u32;
            tmp_array;
        }), size_t, num_fields)  

        ctf_integer(uint32_t, rule_pos, rule_pos)
        ctf_integer(const void*, entry_ptr, entry_ptr)
        ctf_integer(int, key_found, key_found)
        ctf_integer_hex(const void*, ctx, ctx)
    )
)

/** 
 * Add a bulk of entries to an ACL table
 */
#define trace_acl_entry_add_bulk(tbl, name_id, num_fields, n_keys, keys,             \
    key_found, action_table, pos, ctx)                                              \
    for (unsigned int i = 0; i < n_keys; i++) {                                      \
        struct rte_table_acl_rule_add_params *rule = keys[i];                        \
        void* entry_ptr =  pos[i] == 0 ? NULL :  action_table[pos[i]];          \
        tracepoint(librte_table_acl, rte_table_acl_entry_add, tbl, name_id,          \
            num_fields, rule, pos[i], entry_ptr, key_found[i], ctx);                     \
    }

/** 
 * Delete an entry from an ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_entry_delete,
    TP_ARGS(
        const void*, tbl,
        uint32_t, name_id,
        uint32_t, rule_pos,
        const void*, entry_ptr,
        const void*, ctx
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_integer(uint32_t, rule_pos, rule_pos)
        ctf_integer(const void*, entry_ptr, entry_ptr)
        ctf_integer_hex(const void*, ctx, ctx)     
    )
)

/** 
 * Delete a bulk of entries from an ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_entry_delete_bulk,
    TP_ARGS(
        const void*, tbl,
        uint32_t, name_id,
        uint32_t, n_keys,
        uint32_t*, rule_pos,
        void**, entries_ptr,
        const void*, ctx
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_sequence(void*, rule_pos, rule_pos, size_t, n_keys)
        ctf_sequence(void*, entries_ptr, entries_ptr, size_t, n_keys)
        ctf_integer_hex(const void*, ctx, ctx)
    )
)

/** 
 * Lookup for ACL rules matching a burst of packets
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_lookup,
    TP_ARGS(
        const void*, tbl,
        void**, entries_ptr,
        uint32_t*, rule_pos,
        uint32_t, n_pkts_in,     
        uint32_t, n_pkts_out
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_sequence(uint32_t, rule_pos, rule_pos, size_t, n_pkts_in)        
        ctf_sequence(void*, rule_ptr,
        ({
            void* rules[MAX_BURST_PKT_NUM];
            for(int i = 0; i < n_pkts_in; i++)
                rules[i] = (rule_pos[i] == 0 ? 
                    NULL : entries_ptr[rule_pos[i]]);
            
            rules;
        }), size_t, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out) 
    )
)
#endif /* _RTE_TABLE_ACL_TRACE_H */
#include <lttng/tracepoint-event.h>