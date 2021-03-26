#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_eventdev_ring

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_event_ring_trace.h"

#if !defined(_RTE_EVENT_RING_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EVENT_RING_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_eventdev.h>


/**
 * Create an event ring
 *
 * @p name: name of the ring
 * @p h_r: pointer to the low-level ring
 * @p capacity: number of elements to be stored in the ring
 */
TRACEPOINT_EVENT(
    librte_eventdev_ring,
    rte_event_ring_create,
    TP_ARGS(
        const void*, ring,
        const char*, name,
        unsigned int, capacity,
        int, socket_id,
        unsigned int, flags,
        const void*, h_r
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, ring, ring)
        ctf_string(name, name)
        ctf_integer(unsigned int, capacity, capacity)
        ctf_integer(int, socket_id, socket_id)
        ctf_integer(unsigned int, flags, flags)
        ctf_integer_hex(const void*, h_r, h_r)
    )
)

/**
 * Free an event ring
 * @p ring:
 */
TRACEPOINT_EVENT(
    librte_eventdev_ring,
    rte_event_ring_free,
    TP_ARGS(
        const void*, ring
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, ring, ring)
    )
)

/**
 * Enqueue a burst of events to an event ring
 *
 * @p ring: event ring pointer
 * @p n_enq: number of events to enqueue
 * @p free_entries: number of left free entries in the event ring
 */
TRACEPOINT_EVENT(
    librte_eventdev_ring,
    rte_event_ring_enqueue_burst,
    TP_ARGS(
        const void*, ring,
        unsigned int, n_enq,
        uint32_t,  free_entries

    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, ring, ring)
        ctf_integer(unsigned int, n_enq, n_enq)
        ctf_integer(uint32_t, free_entries, free_entries)
    )
)

/**
 * Dequeue a burst of events from an event ring
 *
 * @p ring: event ring pointer
 * @p n_deq: number of elements dequeued from the ring
 * @p remaining:  number of events remaining in the ring once the dequeue has completed
 */
TRACEPOINT_EVENT(
    librte_eventdev_ring,
    rte_event_ring_dequeue_burst,
    TP_ARGS(
        const void*, ring,
        unsigned int, n_deq,
        uint32_t,  remaining

    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, ring, ring)
        ctf_integer(unsigned int, n_deq, n_deq)
        ctf_integer(uint32_t, remaining, remaining)
    )
)
#endif /* _RTE_EVENT_RING_TRACE_H */
#include <lttng/tracepoint-event.h>