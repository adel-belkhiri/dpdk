#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_cryptodev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_cryptodev_trace.h"

#if !defined(_RTE_CRYPTODEV_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_CRYPTODEV_TRACE_H

#include <lttng/tracepoint.h>

/**
 * Configure a crypto device.
 */
TRACEPOINT_EVENT(
    librte_cryptodev,
    rte_cryptodev_configure,
    TP_ARGS(
        const void*, dev,
        uint8_t, dev_id,
        char*, name,
        uint16_t, nb_queue_pairs
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, dev, dev)
        ctf_integer(uint16_t, dev_id, dev_id)
        ctf_string(name, name)
        ctf_integer(uint16_t, nb_queue_pairs, nb_queue_pairs)
    )
)

/**
 * Start an Ethernet device.
 */
TRACEPOINT_EVENT(
    librte_cryptodev,
    rte_cryptodev_start,
    TP_ARGS(
        uint16_t, dev_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, dev_id, dev_id)
    )
)

/**
 * Stop a crypto device.
 */
TRACEPOINT_EVENT(
    librte_cryptodev,
    rte_cryptodev_stop,
    TP_ARGS(
        uint16_t, dev_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, dev_id, dev_id)
    )
)

TRACEPOINT_EVENT(
    librte_cryptodev,
    rte_cryptodev_close,
    TP_ARGS(
        uint16_t, dev_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, dev_id, dev_id)
    )
)

#endif /* _RTE_CRYPTODEV_TRACE_H */

#include <lttng/tracepoint-event.h>
