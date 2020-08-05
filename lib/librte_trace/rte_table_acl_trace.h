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
 * @p tbl 
 * @p name
 * @p max_rule_num
 * @p rule_size
 * @p num_categories: The number of categories is fixed to 1. 
 * @p mem_max_size
 * @p entry_size
 * @p field_def_type Type of the field :
 *          0 : RTE_ACL_FIELD_TYPE_MASK
 *          1 : RTE_ACL_FIELD_TYPE_RANGE
 *          2 : RTE_ACL_FIELD_TYPE_BITMASK
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
 * Free an ACL table
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
 * 
 * @p name_id: This field alternates between 1 and 0. It is used by the ACL table to create ACL context with
 * differrent names table_name_a or table_name_b.
 * @p rule_pos: Index of the rule. Each rule has a uniq index which is its position in the table.
 * @p key_found: Indicates whether the rule exists already in the table or not. In the latter case only the 
 * action part of the rule is updated.
 * @p ctx: Pointer on the low-level acl context (different after each entry_add/delete).
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
        ctf_integer(int, key_found, key_found)
        ctf_integer_hex(const void*, ctx, ctx)
    )
)

/** 
 * Add a bulk of entries to the ACL table
 */
#define trace_acl_entry_add_bulk(tbl, name_id, num_fields, n_keys, keys,             \
    key_found, pos, ctx)                                                             \
    for (unsigned int i = 0; i < n_keys; i++) {                                      \
        struct rte_table_acl_rule_add_params *rule = keys[i];                        \
        tracepoint(librte_table_acl, rte_table_acl_entry_add, tbl, name_id,          \
            num_fields, rule, pos[i], key_found[i], ctx);                            \
    }

/** 
 * Delete an entry from the ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_entry_delete,
    TP_ARGS(
        const void*, tbl,
        uint32_t, name_id,
        uint32_t, rule_pos,
        const void*, ctx
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_integer(uint32_t, rule_pos, rule_pos)
        ctf_integer_hex(const void*, ctx, ctx)     
    )
)

/** 
 * Delete a bulk of entries from the ACL table
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_entry_delete_bulk,
    TP_ARGS(
        const void*, tbl,
        uint32_t, name_id,
        uint32_t, n_keys,
        uint32_t*, rule_pos,
        const void*, ctx
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, name_id, name_id)
        ctf_sequence(uint32_t, rule_pos, rule_pos, size_t, n_keys)
        ctf_integer_hex(const void*, ctx, ctx)
    )
)

/** 
 * Lookup for ACL rules matching a burst of packets
 * @p n_pkts_in: Number of packets feeded to the lookup function.
 * @p n_pkts_out: Number of matching packets.
 * @p rule_pos: Each rule has a uniq position. It is used as an ID.
 */
TRACEPOINT_EVENT(
    librte_table_acl,
    rte_table_acl_lookup,
    TP_ARGS(
        const void*, tbl,
        uint32_t*, rule_pos,
        uint32_t, n_pkts_in,
        uint32_t, n_pkts_out
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_sequence(uint32_t, rule_pos, rule_pos, size_t, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out)
    )
)
#endif /* _RTE_TABLE_ACL_TRACE_H */
#include <lttng/tracepoint-event.h>