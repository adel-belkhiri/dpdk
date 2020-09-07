#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_pipeline

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_pipeline_trace.h"

#if !defined(_RTE_PIPELINE_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_PIPELINE_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_pipeline.h>
#include <rte_port_in_action.h>

/**
 * Create a pipeline
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_create,
    TP_ARGS(
        const void*, p,
        const char*, name,
        int, socket_id,
        uint32_t, offset_port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, p, p)
        ctf_string(name, name)
        ctf_integer(int, socket_id, socket_id)
        ctf_integer(uint32_t, offset_port_id, offset_port_id)
    )
)

/**
 * Free a pipeline
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_free,
    TP_ARGS(
        const void*, p
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
    )
)

/**
 * Pipeline input port create
 *
 * @p port_id: Port identifier
 * @p burst_size: Number of packets to read in a single shot.
 * @p f_action: Function to apply upon each received packet
 * @p h_port: pointer to the low-level rte_port(ex. rte_ring_port, ..)
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_in_create,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        uint32_t, burst_size,
        const void*, f_action,
        const void*, h_port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer(uint32_t, burst_size, burst_size)
        ctf_integer_hex(void*, f_action, f_action)
        ctf_integer_hex(void*, h_port, h_port)
    )
)

/**
 * Pipeline output port create
 *
 * @p p: pointer to the rte_pipeline data structure
 * @p port_id: port identifier
 * @p h_port: pointer to the low-level rte_port data structure
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_out_create,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        const void*, f_action,
        const void*, h_port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer_hex(void*, f_action, f_action)
        ctf_integer_hex(void*, h_port, h_port)
    )
)

/**
 * Pipeline input port free
 *
 * @p h_port: pointer to the low-level rte_port data structure
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_in_free,
    TP_ARGS(
        const void*, h_port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, h_port, h_port)
    )
)

/**
 * Pipeline output port free
 *
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_out_free,
    TP_ARGS(
        const void*, h_port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, h_port, h_port)
    )
)

/**
 * Connect a pipeline input port to a table
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_in_connect_to_table,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        uint32_t, table_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer(uint32_t, table_id, table_id)
    )
)

/**
 * Enable a pipeline input port
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_in_enable,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
    )
)

/**
 * Disable a pipeline input port
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_port_in_disable,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
    )
)

/**
 * Create a pipeline table
 *
 * RTE_PIPELINE_ACTION_DROP is the default action to apply in case of a lookup miss
 * (if default_entry is defined).
 *
 * @p f_hit_action: Pointer to the function to execute if a packet matches with a rule
 * @p f_miss_action: Pointer to the function to execute in case a packet didnt match with any
 * of table's rules.
 * @p h_table: pointer to the low-level rte_table_{acl, lpm, hash, etc.}
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_table_create,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, entry_size,
        const void*, f_hit_action,
        const void*, f_miss_action,
        const void*, h_table
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, entry_size, entry_size)
        ctf_integer_hex(void*, f_hit_action, f_hit_action)
        ctf_integer_hex(void*, f_miss_action, f_miss_action)
        ctf_integer_hex(void*, h_table, h_table)
    )
)

/**
 * Pipeline table free
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_table_free,
    TP_ARGS(
        const void*, h_table
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, h_table, h_table)
    )
)

/**
 * Add a default entry to a pipeline table.
 *
 * @p next_port_table_id: ID of the port/table to send the packet to if default action is equal
 * to RTE_PIPELINE_ACTION_PORT/RTE_PIPELINE_ACTION_TABLE.
 *
 * Values of actions are described by rte_pipeline_action enumeration :
 *
 *  enum rte_pipeline_action {
        // Drop the packet
        RTE_PIPELINE_ACTION_DROP = 0,

        // Send packet to output port
        RTE_PIPELINE_ACTION_PORT,

        // Send packet to output port read from packet meta-data
        RTE_PIPELINE_ACTION_PORT_META,

        // Send packet to table
        RTE_PIPELINE_ACTION_TABLE,

        // Number of reserved actions
        RTE_PIPELINE_ACTIONS
    };
*/
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_table_default_entry_add,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint8_t, action,
        uint32_t, next_port_table_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint8_t, action, action)
        ctf_integer(uint32_t, next_port_table_id, next_port_table_id)
    )
)

/**
 * Set next table id in the "table chain"
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    set_next_table_id,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, next_table_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, next_table_id, next_table_id)
    )
)

/**
 * Delete the default entry of a pipeline table and restore its default action (
 * RTE_PIPELINE_ACTION_DROP).
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_table_default_entry_delete,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
    )
)

/**
 * Add a rule to a pipeline table
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_pipeline_table_entry_add,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        struct rte_pipeline_table_entry*, entry,
        const void*, entry_ptr,
        uint32_t, key_found

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint8_t, action, entry->action)
        ctf_integer(uint8_t, next_port_table_id, entry->table_id)
        ctf_integer_hex(void*, entry_ptr, entry_ptr)
        ctf_integer(uint32_t, key_found, key_found)
    )
)

/**
 * Number of packets dropped by port action function handler
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    port_in_ah_drop,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)


/**
 * Number of packets dropped by port action function handler
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    port_out_ah_drop,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)

/**
 * Number of packets dropped by a table action handler upon
 * lookup hit
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    table_drop_by_lkp_hit_ah,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)

/**
 * Number of packets dropped by a table action handler upon
 * lookup miss
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    table_drop_by_lkp_miss_ah,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)

/**
 * Number of packets dropped by a table upon lookup miss (execution of default action)
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    table_drop_by_lkp_miss,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)

/**
 * Number of packets dropped by a table upon lookup hit (execution of matching rule)
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    table_drop_by_lkp_hit,
    TP_ARGS(
        const void*, p,
        uint32_t, table_id,
        uint32_t, nb_pkts_drop

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, table_id, table_id)
        ctf_integer(uint32_t, nb_pkts_drop, nb_pkts_drop)
    )
)

/**
 * Number of packets forwarded by a table to a child table.
 *
 * @p port_id: ID of the port receiving the trafic.
 * @p from_tbl_id : ID of the table source of the trafic.
 * @p to_tbl_id: ID of the child table.
 * @p nb_pkts: Number of packets transferred to child table.
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    forward_to_next_table,
    TP_ARGS(
        const void*, p,
        uint32_t, port_id,
        uint32_t, from_tbl_id,
        uint32_t, to_tbl_id,
        uint32_t, nb_pkts

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, p, p)
        ctf_integer(uint32_t, port_id, port_id)
        ctf_integer(uint32_t, from_tbl_id, from_tbl_id)
        ctf_integer(uint32_t, to_tbl_id, to_tbl_id)
        ctf_integer(uint32_t, nb_pkts, nb_pkts)
    )
)

/**
 * Create an input port action profile .
 *
 * @p profile: pointer on the action profile data structure
 * @p socket_id: CPU socket ID (for the internal data structures memory allocation).
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_profile_create,
    TP_ARGS(
        const void*, profile,
        int, socket_id
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
        ctf_integer(int, socket_id, socket_id)
    )
)

/**
 * Free an input port action profile .
 *
 * @p profile: pointer on the action profile data structure used as an ID.
 * @p socket_id: CPU socket ID (for the internal data structures memory allocation).
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_profile_free,
    TP_ARGS(
        const void*, profile
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
    )
)

/*
 * Freeze an input port action profile .
 *
 * Once this function is called successfully, the given profile enters the
 * frozen state with the following immediate effects: no more actions can be
 * registered for this profile, so the profile can be instantiated to create
 * input port action objects.
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_profile_freeze,
    TP_ARGS(
        const void*, profile
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
    )
)

/**
 * register an action in the Input port action profile .
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    port_in_action_profile_action_fltr_register,
    TP_ARGS(
        const void*, profile,
        struct rte_port_in_action_fltr_config*, cfg
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
        ctf_integer(uint32_t, key_offset, cfg->key_offset)
        ctf_integer_hex(uint64_t, key_mask0, ((uint64_t *) cfg->key_mask)[0])
        ctf_integer_hex(uint64_t, key_mask1, ((uint64_t *) cfg->key_mask)[1])
        ctf_integer(int, filter_on_match, cfg->filter_on_match)
        ctf_integer(uint32_t, port_id, cfg->port_id)
    )
)


/**
 * register an action in the Input port action profile .
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    port_in_action_profile_action_lb_register,
    TP_ARGS(
        const void*, profile,
        struct rte_port_in_action_lb_config*, cfg
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
        ctf_integer(uint32_t, key_size, cfg->key_size)
        ctf_integer(uint32_t, key_offset, cfg->key_offset)
        ctf_integer_hex(uint64_t, key_mask0, ((uint64_t *) cfg->key_mask)[0])
        ctf_integer_hex(uint64_t, key_mask1, ((uint64_t *) cfg->key_mask)[1])
        ctf_integer(uint64_t, seed, cfg->seed)
        ctf_array(uint32_t, port_id, cfg->port_id, RTE_PORT_IN_ACTION_LB_TABLE_SIZE)
    )
)

#define trace_rte_port_in_action_profile_action_register(profile, action_config, type)   \
    do {                                                                             \
        if (type == RTE_PORT_IN_ACTION_FLTR) {                                       \
            tracepoint(librte_pipeline, port_in_action_profile_action_fltr_register, \
                profile, action_config);                                             \
        } else if(type == RTE_PORT_IN_ACTION_LB) {                                   \
            tracepoint(librte_pipeline, port_in_action_profile_action_lb_register,   \
                profile, action_config);                                             \
        }                                                                            \
    } while(0);

/*
 * Instantiates the given input port action profile to create an input port
 * action object.
 *
 * @p profile: action profile id
 * @p action: action id
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_create,
    TP_ARGS(
        const void*, profile,
        const void*, action
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, profile, profile)
        ctf_integer_hex(const void*, action, action)
    )
)

/**
 * Modify the output port_id of a filter action.
 *
 * @p port_id: output port id
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_fltr_apply,
    TP_ARGS(
        const void*, action,
        uint32_t, port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, action, action)
        ctf_integer(uint32_t, port_id, port_id)
    )
)

/**
 * Modify the output port_ids of a load balancing action.
 *
 * @p port_id: output ports ids
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_lb_apply,
    TP_ARGS(
        const void*, action,
        uint32_t*, port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, action, action)
        ctf_sequence(uint32_t, port_id, port_id, size_t, sizeof(port_id))
    )
)

/**
 * Input port action free.
 *
 * @p action:
 *   Handle to input port action object.
 */
TRACEPOINT_EVENT(
    librte_pipeline,
    rte_port_in_action_free,
    TP_ARGS(
        const void*, action
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, action, action)
    )
)

//TODO: To instrument table profiles : rte_table_action.c
#endif /* _RTE_PIPELINE_TRACE_H */

#include <lttng/tracepoint-event.h>