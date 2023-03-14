#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_port_ring

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_port_ring_trace.h"

#if !defined(_RTE_PORT_RING_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_PORT_RING_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_port_ring.h>


/**
 * Create a port ring reader
 * @p flags: Flags supplied at creation
 * @p ring : pointer on the ring structure
 * @p size: Size of ring
 * @p capacity:  Usable size of ring
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_reader_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_ring_reader_params *, conf
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_string(name, conf->ring->name)
        ctf_integer(int, flags, conf->ring->flags)
        ctf_integer(uint32_t, size, conf->ring->size)
        ctf_integer(uint32_t, capacity, conf->ring->capacity)
        ctf_integer_hex(const void*, ring, conf->ring)
    )
)

 /** @p nb_pkts: Number of packets to dequeue from the ring
 *   @p rx_pkt_cnt: Actual number of objects dequeued, 0 if ring is empty
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_reader_rx,
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
    librte_port_ring,
    rte_port_ring_reader_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, port, port)
    )
)

/**
 * Create a port ring writer
 * @p flags: Flags supplied at creation
 * @p size: Size of ring
 * @p capacity:  Usable size of ring
 * @p tx_burst_sz: Recommended burst size to the ring. The actual burst size can be
	bigger or smaller than this value.
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_writer_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_ring_writer_params *, conf
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_string(name, conf->ring->name)
        ctf_integer(int, flags, conf->ring->flags)
        ctf_integer(uint32_t, size, conf->ring->size)
        ctf_integer(uint32_t, capacity, conf->ring->capacity)
        ctf_integer(uint32_t, tx_burst_sz, conf->tx_burst_sz)
        ctf_integer_hex(const void*, ring, conf->ring)
    )
)

 /**
 *  Enqueue a burst of packets in the port ring.
 *
 * @p tx_buf_count: Number of packets to enqueue in the ring
 * @p tx_pkt_cnt: Actual number of objects enqueued. If nb_tx < tx_buf_count the remaining
 * packets are simply deleted
 */
TRACEPOINT_EVENT(
    librte_port_ring,
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

 /**
 *  Enqueue a burst of packets in the port ring.
 *
 * @p tx_buf_count: Number of packets to enqueue in the ring
 * @p tx_pkt_cnt: Actual number of objects enqueued. If nb_tx < tx_buf_count the remaining
 * packets are simply deleted
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    send_burst_mp,
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

/**
 * Write a packet to the port ring. If the number of written packets (tx_buf_count) exceeded
 * the value port->tx_burst_sz, then a send_burst is executed
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_writer_tx,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
    )
)

/**
 * Write a bulk of packet to the port ring.
 *
 * @p n_pkts: number of packets to send
 * @p tx_n_pkts: number of packet that are sent
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_writer_tx_bulk,
    TP_ARGS(
        const void*, port,
        uint32_t, n_pkts,
        uint32_t, tx_n_pkts
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint32_t, n_pkts, n_pkts)
        ctf_integer(uint32_t, tx_n_pkts, tx_n_pkts)
    )
)
/**
 * Free a port
 */
TRACEPOINT_EVENT(
    librte_port_ring,
    rte_port_ring_writer_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, port, port)
    )
)
#endif /* _RTE_PORT_RING_TRACE_H */

#include <lttng/tracepoint-event.h>
