#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_ethdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_ethdev_trace.h"

#if !defined(_RTE_ETHDEV_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_ETHDEV_TRACE_H

#include <lttng/tracepoint.h>


TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_create,
    TP_ARGS(
        uint16_t, port_id,
        const char*, name
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_string(name, name)
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_destroy,
    TP_ARGS(
        const char*, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_tx_queue_setup,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id,
        uint16_t, nb_desc,
        unsigned int, socket_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint16_t, nb_desc, nb_desc)
        ctf_integer(unsigned int, socket_id, socket_id)                
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_rx_queue_setup,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id,
        uint16_t, nb_desc,
        unsigned int, socket_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint16_t, nb_desc, nb_desc)
        ctf_integer(unsigned int, socket_id, socket_id)                
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_tx_queue_start,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)            
    )    
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_rx_queue_start,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)            
    )
)


TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_tx_queue_stop,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)            
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_rx_queue_stop,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)            
    )
)
#endif /* _RTE_ETHDEV_TRACE_H */

#include <lttng/tracepoint-event.h>
