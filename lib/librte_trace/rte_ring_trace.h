#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_ring

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_ring_trace.h"

#if !defined(__RTE_RING_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __RTE_RING_TRACE_H

#include <lttng/tracepoint.h>

/**
 * Create a ring
 * @p ring:
 * @p name:
 * @p count:
 * @p socket_id:
 */
TRACEPOINT_EVENT(
    librte_ring,
    rte_ring_create,
    TP_ARGS(
        const void*, ring,
        char*, name,
        unsigned int, count,
        int, socket_id
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, ring, ring)
        ctf_string(name, name)
        ctf_integer(unsigned int, count, count)
        ctf_integer(int, socket_id, socket_id)
    )
)

/**
 * Free a ring
 */
TRACEPOINT_EVENT(
    librte_ring,
    rte_ring_free,
    TP_ARGS(
        const void*, ring
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, ring, ring)
    )
)
 /**
  * Dequeue n entries from a ring
  *
  *  @p n: Number of packets dequeued from the ring
  *  @p available: Number of remaining ring entries after the dequeue has finished
  */
// TRACEPOINT_EVENT(
//     librte_ring,
//     rte_ring_dequeue,
//     TP_ARGS(
//         const void*, ring,
//         unsigned int, n,
//         unsigned int, available
//     ),
//     TP_FIELDS(
//         ctf_integer_hex(const void*, ring, ring)
//         ctf_integer(unsigned int, n, n)
//         ctf_integer(unsigned int, available, available)
//     )
// )

 /**
 *  Enqueue entries to the ring.
 *
 * @p n: Number of packets enqueued to the ring
 * @p free_entries: amount of space after the enqueue operation has finished
 */
//TRACEPOINT_EVENT(
//     librte_ring,
//     rte_ring_enqueue,
//     TP_ARGS(
//         const void*, ring,
//         unsigned int, n,
//         unsigned int, free_entries
//     ),
//     TP_FIELDS(
//         ctf_integer_hex(const void*, ring, ring)
//         ctf_integer(unsigned int, n, n)
//         ctf_integer(unsigned int, free_entries, free_entries)
//     )
// )


#endif /* __RTE_RING_TRACE_H */

#include <lttng/tracepoint-event.h>