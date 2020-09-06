#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_port_ethdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_port_ethdev_trace.h"

#if !defined(_RTE_PORT_ETHDEV_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_PORT_ETHDEV_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_port_ethdev.h>


/**
 * Create a port ethdev reader. The "port_ethdev_reader" is a wrapper class to
 * read/write from an Ethernet device queue.
 * @p port_id: Identifier of the Ethernet device
 * @p queue_id: Identifier of the device queue
 */
TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_reader_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_ethdev_reader_params *, conf
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint16_t, port_id, conf->port_id)
        ctf_integer(uint16_t, queue_id, conf->queue_id)
    )
)

TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_reader_rx,
    TP_ARGS(
        const void*, port,
        uint32_t, nb_pkts,
        uint32_t, rx_pkt_cnt
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint32_t, nb_pkts, nb_pkts)
        ctf_integer(uint32_t, rx_pkt_cnt, rx_pkt_cnt)
    )
)

/**
 * Free a port
 */
TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_reader_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, port, port)
    )
)

/**
 * Create a port ring writer
 * @p port: Flags supplied at creation
 * @p size: Size of ring
 * @p capacity:  Usable size of ring
 * @p tx_burst_sz: Recommended burst size to the ring. The actual burst size can be
	bigger or smaller than this value.
 */
TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_writer_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_ethdev_writer_params *, conf
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint16_t, port_id, conf->port_id)
        ctf_integer(uint16_t, queue_id, conf->queue_id)
        ctf_integer(uint32_t, tx_burst_sz, conf->tx_burst_sz)
    )
)

 /**
 *  Enqueue a burst of packets in the port ring.
 *
 * @p tx_buf_count: Number of packets to enqueue in the ring
 * @p nb_tx: Actual number of objects enqueued. If nb_tx < tx_buf_count the remaining
 * packets are simply deleted
 */
TRACEPOINT_EVENT(
    librte_port_ethdev,
    send_burst,
    TP_ARGS(
        const void*, port,
        uint32_t, tx_pkt_cnt,
        uint32_t, tx_buf_count
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint32_t, tx_pkt_cnt, tx_pkt_cnt)
        ctf_integer(uint32_t, tx_buf_count, tx_buf_count)
    )
)

TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_writer_tx,
    TP_ARGS(
        const void*, port,
        uint32_t, tx_buf_count
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint32_t, tx_buf_count, tx_buf_count)
    )
)

/**
 * Free a port
 */
TRACEPOINT_EVENT(
    librte_port_ethdev,
    rte_port_ethdev_writer_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, port, port)
    )
)
#endif /* _RTE_PORT_ETHDEV_TRACE_H */

#include <lttng/tracepoint-event.h>