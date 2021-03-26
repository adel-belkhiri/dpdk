#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER dsw_eventdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_event_dsw_trace.h"

#if !defined(_RTE_EVENT_DSW_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EVENT_DSW_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_eventdev.h>


/**
 * Probe a dsw device
 *
 * @p name: name of sw
 * @p dsw: software event device
 * @p eventdev: pointer to the internal eventdev data structure
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_probe,
    TP_ARGS(
        const char*, name,
        void*, dsw,
        uint8_t, dev_id
    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, dev_id, dev_id)
    )
)

/**
 * Configure a dsw
 * @p dev_id:
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_configure,
    TP_ARGS(
        void*, dsw,
        int32_t, max_inflight,
        const struct rte_event_dev_config*, conf
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint32_t, max_inflight, max_inflight)
        /*ctf_integer(uint32_t, dequeue_timeout_ns, conf->dequeue_timeout_ns)
        ctf_integer(int32_t, nb_events_limit, conf->nb_events_limit)
        ctf_integer(uint8_t, nb_event_queues, conf->nb_event_queues)
        ctf_integer(uint8_t, nb_event_ports, conf->nb_event_ports)
        ctf_integer(uint32_t, nb_event_queue_flows, conf->nb_event_queue_flows)
        ctf_integer(uint32_t, nb_event_port_dequeue_depth, conf->nb_event_port_dequeue_depth)
        ctf_integer(uint32_t, nb_event_port_enqueue_depth, conf->nb_event_port_enqueue_depth)*/
    )
)

/**
 * Setup a dsw port
 *
 * @p dsw: distributed software event device
 * @p port_id: port ID
 * @p in_ring: pointer to port RX ring
 * @p ctl_in_ring: pointer to port CQ ring
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_setup,
    TP_ARGS(
        void*, dsw,
        uint8_t, port_id,
        const struct rte_event_port_conf*, conf,
        void*, in_ring,
        void*, ctl_in_ring,
        uint64_t, load_update_interval,
	    uint64_t, migration_interval

    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_integer(int32_t, new_event_threshold, conf->new_event_threshold)
        ctf_integer(uint8_t, disable_implicit_release, conf->disable_implicit_release)
        ctf_integer(uint16_t, dequeue_depth, conf->dequeue_depth)
        ctf_integer(uint16_t, enqueue_depth, conf->enqueue_depth)

        ctf_integer_hex(void*, in_ring, in_ring)
        ctf_integer_hex(void*, ctl_in_ring, ctl_in_ring)
        ctf_integer(uint16_t, load_update_interval, load_update_interval)
        ctf_integer(uint16_t, migration_interval, migration_interval)
    )
)

/**
 * Set up an event queue for the dsw
 *
 * @p dev_id:
 * @p queue_id:
 * @p schedule_type:
 *          - RTE_SCHED_TYPE_ATOMIC  : 1
 *          - RTE_SCHED_TYPE_PARALLEL : 2
 *
 * @p event_queue_cfg:
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_queue_setup,
    TP_ARGS(
        void*, dsw,
        uint8_t, queue_id,
        uint8_t, schedule_type,
        const struct rte_event_queue_conf*, queue_conf
    ),
    TP_FIELDS(
        ctf_integer(void*, dsw, dsw)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint8_t, schedule_type, schedule_type)
    )
)

/**
 * Enqueue events to port rx ring.
 *
 * @p sw : eventdev sw
 * @p port: port
 * @p s_inflights: coarse-grained estimation of the number of new events in this eventdev instance
 * @p p_inflight_credits: credits assigned to the port
 * @p out_rels: number of outstanding event releases
 * @p num: number of events to enqueue. If there are fewer inflight credits than new events,
		the number of events to enqueue is limited
 * @p n_enq: number of events that were enqueued
 * @p n_new: number of new events
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_event_enqueue_burst,
    TP_ARGS(
        void*, dsw,
        uint8_t, port_id,
        uint16_t, n_enq,
        uint16_t, n_new,
        uint16_t, n_release,
        uint16_t, n_non_release
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint16_t, n_enq, n_enq)
        ctf_integer(uint16_t, n_new, n_new)
        ctf_integer(uint16_t, n_forward, n_non_release - n_new)
        ctf_integer(uint16_t, n_release, n_release)
    )
)

/**
 * Dequeue events from port consumer ring.
 *
 * @p sw : eventdev sw
 * @p port_id: port identifier
 * @p num: number of events to dequeue
 * @p n_deq: number of events that are really dequeued
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_event_dequeue_burst,
    TP_ARGS(
        void*, dsw,
        uint8_t, port_id,
        uint16_t, num,
        uint16_t, n_deq
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint16_t, num, num)
        ctf_integer(uint16_t, n_deq, n_deq)
    )
)

TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_acquire_credits,
    TP_ARGS(
        void*, dsw,
        uint8_t, port_id,
        int32_t, required_credits,
        int32_t, p_inflight_credits,
        int32_t, dsw_credits_on_loan
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(int32_t, required_credits, required_credits)
        ctf_integer(int32_t, p_inflight_credits, p_inflight_credits)
        ctf_integer(int32_t, dsw_credits_on_loan, dsw_credits_on_loan)
    )
)

TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_load_update,
    TP_ARGS(
        void*, dsw,
        uint8_t, port_id,
        int16_t, current_load
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(int16_t, current_load, current_load)
    )
)

/**
 * Start the migration of a flow from one port to another.
 *
 * @p sw : eventdev dsw
 * @p src_port_id: source port identfier
 * @p dst_port_id: target port identfier
 * @p queue_id: queue identifier
 * @p flow_hash: hash value of the flow identifier
 * port migration state change to DSW_MIGRATION_STATE_PAUSING
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_start_migration,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id,
        uint8_t, dst_port_id,
        uint8_t, queue_id,
        uint16_t, flow_hash
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
        ctf_integer(uint8_t, dst_port_id, dst_port_id)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint16_t, flow_hash, flow_hash)
    )
)

TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_move_migrating_flow,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id,
        uint8_t, dst_port_id,
        uint8_t, queue_id,
        uint16_t, flow_hash
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
        ctf_integer(uint8_t, dst_port_id, dst_port_id)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint16_t, flow_hash, flow_hash)
    )
)

/**
 * Source port has collected all confirmation msgs from other ports.
 *
 * @p sw : eventdev dsw
 * @p port_id: source port identfier
 * port migration state change to either DSW_MIGRATION_STATE_FORWARDING (confirm FLOW_PAUS)
 *  or to DSW_MIGRATION_STATE_IDLE (confirm FLOW_UNPAUS)
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    collect_all_confirm_msgs,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
    )
)

/**
 * Finish the migration of a flow from one port to another.
 *
 * @p sw : eventdev dsw
 * @p port_id: source port identfier
 * @p queue_id: queue identifier
 * @p flow_hash: hash value of the flow identifier
 * port migration state change to DSW_MIGRATION_STATE_IDLE
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_end_migration,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id,
        uint8_t, queue_id,
        uint16_t, flow_hash
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint16_t, flow_hash, flow_hash)
    )
)

/**
 * Close the dsw device
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_close,
    TP_ARGS(
        void*, dsw
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)

    )
)

/**
 * Start the dsw device
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_start,
    TP_ARGS(
        void*, dsw,
        uint64_t, now
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint64_t, now, now)
    )
)

/**
 * Stop the dsw device
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_stop,
    TP_ARGS(
        void*, dsw
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)

    )
)
/**
 * Remove the dsw device
 *
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_remove,
    TP_ARGS(
        const char*, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

/**
 * Based on the flow_hash and queue_id, and according to the scheduling function
 * (dsw_schedule) one event is moved to dest_port
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_buffer_non_paused,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id,
        uint8_t, dst_port_id,
        uint8_t, queue_id,
        uint16_t, flow_hash
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
        ctf_integer(uint8_t, dst_port_id, dst_port_id)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint16_t, flow_hash, flow_hash)
    )
)

/**
 * Once the migration is done, flush all the events in a paused flow
 */
TRACEPOINT_EVENT(
    dsw_eventdev,
    dsw_port_flush_paused_events,
    TP_ARGS(
        void*, dsw,
        uint8_t, src_port_id,
        uint8_t, dst_port_id,
        uint8_t, queue_id,
        uint16_t, flow_hash
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dsw, dsw)
        ctf_integer(uint8_t, src_port_id, src_port_id)
        ctf_integer(uint8_t, dst_port_id, dst_port_id)
        ctf_integer(uint8_t, queue_id, queue_id)
        ctf_integer(uint16_t, flow_hash, flow_hash)
    )
)
#endif /* _RTE_EVENT_DSW_TRACE_H */
#include <lttng/tracepoint-event.h>