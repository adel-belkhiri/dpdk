#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_acl

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_acl_trace.h"

#if !defined(_RTE_ACL_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_ACL_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_acl.h>

/** Number of elements in the array. */
#define	ARRAY_DIM(a)	(sizeof (a) / sizeof ((a)[0]))


/**
 * Create a new ACL context.
 */
TRACEPOINT_EVENT(
    librte_acl,
    rte_acl_create,
    TP_ARGS(
        const void *, ctx,
        const struct rte_acl_param *, param
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, ctx, ctx)
        ctf_integer(uint32_t, socket_id, param->socket_id)
        ctf_string(name, param->name)
        ctf_integer(uint32_t, max_rules, param->max_rule_num)
        ctf_integer(uint32_t, rule_sz, param->rule_size)
    )
)

/**
 * Free all memory used by ACL context.
 */
TRACEPOINT_EVENT(
    librte_acl,
    rte_acl_free,
    TP_ARGS(
        const void *, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

/**
 * Add an ACL rule to the context.
 */
TRACEPOINT_EVENT(
    librte_acl,
    rte_acl_add_rule,
    TP_ARGS(
        const void *, ctx,
        struct rte_acl_rule_data *, data,
        struct rte_acl_field*, field,
        size_t, num_fields
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, ctx, ctx)
        ctf_integer(uint32_t, category_mask, data->category_mask)
        ctf_integer(int32_t, priority, data->priority)
        ctf_integer(uint32_t, userdata, data->userdata)

        ctf_sequence(uint32_t, field_value,
        ({
            uint32_t tmp_array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < num_fields; i++)
                tmp_array[i] = (uint32_t) field[i].value.u32;
            tmp_array;
        }), size_t, num_fields)

        ctf_sequence(uint32_t, field_mask,
        ({
            uint32_t tmp_array[RTE_ACL_MAX_FIELDS];
            for(int i = 0; i < num_fields; i++)
                tmp_array[i] = (uint32_t) field[i].mask_range.u32;
            tmp_array;
        }), size_t, num_fields)
    )
)

/**
 * Bulk adding ACL rules to the context
 */
#define trace_acl_rules(ctx, num, rules)        \
    for(uint32_t j = 0; j < num; j++ ) {        \
        struct rte_acl_rule *rv = (struct rte_acl_rule *)   \
			((uintptr_t)rules + j * ctx->rule_sz);          \
        size_t num_fields =  (ctx->rule_sz - sizeof(rv->data)) / sizeof(rv->field[0]);      \
        tracepoint(librte_acl, rte_acl_add_rule, ctx, &rv->data, rv->field, num_fields);    \
    }

/**
 * Generate a RT data structures from the rules
 */
TRACEPOINT_EVENT(
    librte_acl,
    rte_acl_build,
    TP_ARGS(
        const void *, ctx,
        const struct rte_acl_config*, cfg,

        uint32_t, node_max,
        uint32_t, num_nodes,
        uint32_t, num_tries,
        size_t, mem_sz
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, ctx, ctx)
        ctf_integer(uint32_t, num_categories, cfg->num_categories)
        ctf_integer(size_t, mem_max_sz, cfg->max_size)
        ctf_integer(uint32_t, node_max, node_max)
        ctf_integer(uint32_t, num_nodes, num_nodes)
        ctf_integer(uint32_t, num_tries, num_tries)
        ctf_integer(size_t, mem_sz, mem_sz)
    )
)

/**
 * Set the classify method for the context
 */
TRACEPOINT_EVENT(
    librte_acl,
    rte_acl_set_ctx_classify,
    TP_ARGS(
        const void *, ctx,
        uint8_t, alg
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, ctx, ctx)
        ctf_integer(uint8_t, alg, alg)
    )
)
#endif /* _RTE_ACL_TRACE_H */
#include <lttng/tracepoint-event.h>