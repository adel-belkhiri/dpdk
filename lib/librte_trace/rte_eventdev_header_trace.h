#if !defined(_RTE_EVENTDEV_HEADER_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EVENTDEV_HEADER_TRACE_H

#include <lttng/tracepoint.h>

/**
 * Enqueue events to an eventdev
 *
 * @p nb_events: number of events to enqueue
 * @p nb_enq_events : number of events that were really enqueued
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_enqueue_burst,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, port_id,
        uint16_t, nb_events,
        uint16_t, nb_enq_events
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_integer(uint16_t, nb_events, nb_events)
        ctf_integer(uint16_t, nb_enq_events, nb_enq_events)
    )
)

/**
 * Enqueue events to an eventdev
 *
 * @p nb_events: number of events to enqueue
 * @p timeout_ticks:
 *          - 0 no-wait, returns immediately if there is no event.
 *          - 0 < wait for the event for timeout_ticks time
 * @p nb_deq_events : number of events that were really dequeued
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_dequeue_burst,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, port_id,
        uint16_t, nb_events,
        uint64_t, timeout_ticks,
        uint16_t, nb_deq_events
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_integer(uint64_t, timeout_ticks, timeout_ticks)
        ctf_integer(uint16_t, nb_events, nb_events)
        ctf_integer(uint16_t, nb_deq_events, nb_deq_events)
    )
)

#endif /* _RTE_EVENTDEV_TRACE_H */