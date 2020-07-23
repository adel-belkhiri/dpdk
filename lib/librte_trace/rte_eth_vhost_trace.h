#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER vhost_pmd

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_eth_vhost_trace.h"

#if !defined(_RTE_ETH_VHOST_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_ETH_VHOST_TRACE_H

#include <lttng/tracepoint.h>

#include <rte_ether.h>

TRACEPOINT_EVENT(
    vhost_pmd,
    eth_dev_vhost_create,
    TP_ARGS(
        const char*, dev_name,
        const char*, ifce_name,
        struct rte_ether_addr *, hw_addr,
        uint16_t, nb_rx_queues,
        uint16_t, nb_tx_queues,
        uint64_t, flags
    ),
    TP_FIELDS(
        ctf_string(dev_name, dev_name)
        ctf_string(ifce_name, ifce_name)
        ctf_array(uint8_t, hw_addr, hw_addr, RTE_ETHER_ADDR_LEN)
        ctf_integer(uint16_t, nb_rx_queues, nb_rx_queues)
        ctf_integer(uint16_t, nb_tx_queues, nb_tx_queues)
        ctf_integer(uint64_t, flags, flags)
    )
)

TRACEPOINT_EVENT(
    vhost_pmd,
    rte_pmd_vhost_remove,
    TP_ARGS(
        const char*, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

TRACEPOINT_EVENT(
    vhost_pmd,
    eth_tx_queue_setup,
    TP_ARGS(
        const char*, dev_name,
        uint16_t, queue_id,
		unsigned int, socket_id,
        uint16_t, virtqueue_id

    ),
    TP_FIELDS(
        ctf_string(dev_name, dev_name)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(unsigned int, socket_id, socket_id)
        ctf_integer(uint16_t, virtqueue_id, virtqueue_id)
    )
)

TRACEPOINT_EVENT(
    vhost_pmd,
    eth_rx_queue_setup,
    TP_ARGS(
        const char*, dev_name,
        uint16_t, queue_id,
		unsigned int, socket_id,
        uint16_t, virtqueue_id
    ),
    TP_FIELDS(
        ctf_string(dev_name, dev_name)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(unsigned int, socket_id, socket_id)
        ctf_integer(uint16_t, virtqueue_id, virtqueue_id)
    )
)

TRACEPOINT_EVENT(
    vhost_pmd,
    queue_setup,
    TP_ARGS(
        const char*, dev_name,
        int, vid,
        uint16_t, port,
        uint16_t, virtqueue_id,
        const char*, type
    ),
    TP_FIELDS(
        ctf_string(dev_name, dev_name)
        ctf_integer(int, vid, vid)
        ctf_integer(uint16_t, port, port)
        ctf_integer(uint16_t, virtqueue_id, virtqueue_id)
        ctf_string(type, type)
    )
)
#endif /* _RTE_ETH_VHOST_TRACE_H */

#include <lttng/tracepoint-event.h>
