#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER sw_eventdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_event_sw_trace.h"

#if !defined(_RTE_EVENT_SW_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EVENT_SW_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_eventdev.h>


/**
 * Probe a software event device
 *
 * @p socket_id:
 * @p name: name of sw
 * @p sw: software event device
 * @p credit_quanta: the value of a credit
 * @p sched_quanta: the value of sched quanta
 * @p service_id: the id of the service running the sw scheduler
 * @p eventdev: pointer to the internal eventdev data structure
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_probe,
    TP_ARGS(
        int, socket_id,
        const char*, name,
        void*, sw,
        uint8_t, dev_id,
        int, credit_quanta,
        int, sched_quanta,
        uint32_t, service_id
    ),
    TP_FIELDS(
        ctf_integer(int, socket_id, socket_id)
        ctf_string(name, name)
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(int, credit_quanta, credit_quanta)
        ctf_integer(int, sched_quanta, sched_quanta)
        ctf_integer(uint32_t, service_id, service_id)

    )
)

/**
 * Setup an eventdev port
 *
 * @p sw: software event device
 * @p port_id: port ID
 * @p rx_worker_ring: pointer to port RX ring
 * @p cq_worker_ring: pointer to port CQ ring
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_port_setup,
    TP_ARGS(
        void*, sw,
        uint8_t, port_id,
        const struct rte_event_port_conf*, conf,
        void*, rx_worker_ring,
        void*, cq_worker_ring
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_integer(int32_t, new_event_threshold, conf->new_event_threshold)
        ctf_integer(uint8_t, disable_implicit_release, conf->disable_implicit_release)
        ctf_integer(uint16_t, dequeue_depth, conf->dequeue_depth)
        ctf_integer(uint16_t, enqueue_depth, conf->enqueue_depth)

        ctf_integer_hex(void*, rx_worker_ring, rx_worker_ring)
        ctf_integer_hex(void*, cq_worker_ring, cq_worker_ring)
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
    sw_eventdev,
    sw_event_enqueue_burst,
    TP_ARGS(
        void*, sw,
        uint8_t, port_id,
        uint16_t, sw_inflights,
        uint16_t, p_inflight_credits,
        uint16_t, outstanding_releases,
        uint16_t, num,
        uint16_t, n_enq,
        int, n_new
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint16_t, sw_inflights, sw_inflights)
        ctf_integer(uint16_t, p_inflight_credits, p_inflight_credits)
        ctf_integer(uint16_t, outstanding_releases, outstanding_releases)
        ctf_integer(uint16_t, num, num)
        ctf_integer(uint16_t, n_enq, n_enq)
        ctf_integer(int, n_new, n_new)
    )
)

/**
 * Dequeue events from port consumer ring.
 *
 * @p sw : eventdev sw
 * @p port: port
 * @p s_inflights: coarse-grained estimation of the number of new events in this eventdev instance
 * @p p_inflight_credits: credits assigned to the port
 * @p outstanding_releases: number of outstanding event releases
 * @p num: number of events to dequeue
 * @p n_deq: number of events that are really dequeued
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_event_dequeue_burst,
    TP_ARGS(
        void*, sw,
        uint8_t, port_id,
        uint16_t, sw_inflights,
        uint16_t, p_inflight_credits,
        uint16_t, outstanding_releases,
        uint16_t, num,
        uint16_t, n_deq,
        uint64_t, zero_polls,
        uint64_t, tot_polls
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint16_t, sw_inflights, sw_inflights)
        ctf_integer(uint16_t, p_inflight_credits, p_inflight_credits)
        ctf_integer(uint16_t, outstanding_releases, outstanding_releases)
        ctf_integer(uint16_t, num, num)
        ctf_integer(uint16_t, n_deq, n_deq)
        ctf_integer(uint64_t, zero_polls, zero_polls)
        ctf_integer(uint64_t, tot_polls, tot_polls)
    )
)


/**
 * Scheduler : transfer events from a single/directed queue to a port cache (port->cq_buf)
 * before pushing it to its CQ ring buffer.
 *
 * @p sw : eventdev sw
 * @p qid_id: queue ID
 * @p iq_num: queue segment ID
 * @p port_id: port ID
 * @p count: number of events transfered
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    schedule_dir_to_cq,
    TP_ARGS(
        void*, sw,
        uint32_t, qid_id,
        uint32_t, iq_num,
        uint8_t, port_id,
        uint32_t, count
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint32_t, qid_id, qid_id)
        ctf_integer(uint32_t, iq_num, iq_num)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint32_t, count, count)
    )
)

/**
 * Scheduler : transfer one event from an atomic queue to a port cq ring.
 *
 * @p sw : eventdev sw
 * @p qid_id: queue ID
 * @p port_id: port ID
 * @p flow_id: flow ID
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    schedule_atomic_to_cq,
    TP_ARGS(
        void*, sw,
        uint32_t, qid_id,
        uint32_t, iq_num,
        uint8_t, port_id,
        uint32_t, flow_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint32_t, qid_id, qid_id)
        ctf_integer(uint32_t, iq_num, iq_num)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint32_t, flow_id, flow_id)
    )
)

/**
 * Scheduler : transfer one event from a parallel queue to a port cq ring.
 *
 * @p sw : eventdev sw
 * @p qid_id: queue ID
 * @p port_id: port ID
 * @p flow_id: flow ID
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    schedule_parallel_to_cq,
    TP_ARGS(
        void*, sw,
        uint32_t, qid_id,
        uint32_t, iq_num,
        uint8_t, port_id,
        uint32_t, flow_id
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint32_t, qid_id, qid_id)
        ctf_integer(uint32_t, iq_num, iq_num)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint32_t, flow_id, flow_id)
    )
)

/**
 * Pull one event from a port RX ring to a SINGLE queue
 *
 * @p sw : eventdev sw
 * @p port: port
 * @p s_inflights: coarse-grained estimation of the number of new events in this eventdev instance
 * @p p_inflight_credits: credits assigned to the port
 * @p outstanding_releases: number of outstanding event releases
 * @p num: number of events to dequeue
 * @p n_deq: number of events that were dequeued
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_schedule_pull_port_dir,
    TP_ARGS(
        void*, sw,
        uint8_t, port_id,
        uint32_t, qid_id,
        uint32_t, iq_num
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint32_t, qid_id, qid_id)
        ctf_integer(uint32_t, iq_num, iq_num)
    )
)

/**
 * Pull one event from a port RX ring to an atomic/parallel queue
 *
 * @p sw : eventdev sw
 * @p port_id: port ID
 * @p qid_id: queue ID
 * @p iq_num: subqueue (according to priority) in which the event was pushed
 * @p allow_order: allow or not the ordering of events. Also indicates the type of the queue
 *          (either ordered or not)
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    pull_port_lb,
    TP_ARGS(
        void*, sw,
        uint8_t, port_id,
        uint32_t, qid_id,
        uint32_t, iq_num,
        int, reordered,
        int, valid
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
        ctf_integer(uint8_t, port_id, port_id)
        ctf_integer(uint32_t, qid_id, qid_id)
        ctf_integer(uint32_t, iq_num, iq_num)
        ctf_integer(int, reordered, reordered)
        ctf_integer(int, valid, valid)
    )
)

/**
 * Close the sw
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_close,
    TP_ARGS(
        void*, sw
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
    )
)

/**
 * Start the sw
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_start,
    TP_ARGS(
        void*, sw
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sw, sw)
    )
)

/**
 * Remove the event device
 *
 */
TRACEPOINT_EVENT(
    sw_eventdev,
    sw_remove,
    TP_ARGS(
        const char*, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

#endif /* _RTE_EVENT_SW_TRACE_H */
#include <lttng/tracepoint-event.h>