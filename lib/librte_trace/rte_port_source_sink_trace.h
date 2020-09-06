#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_port_source_sink

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_port_source_sink_trace.h"

#if !defined(_RTE_PORT_SOURCE_SINK_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_PORT_SOURCE_SINK_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_port_source_sink.h>

/**
 * Create a sink port
 * @p port: pointer to the sink port data structure
 * @p file_name: pcap file name to write to
 * @p max_n_pkts:  maximum number of packets to write to pcap file.
 *                 zero means "infinite".
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_sink_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_sink_params*, params
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_string(pcap_file_name, params->file_name != NULL ? params->file_name : "" )
        ctf_integer(uint32_t, max_n_pkts, params->max_n_pkts)
    )
)

/**
 * Send tx_pkt_cnt to the sink which means drop them. If the port was configured
 * with a pcap filename, packets will be saved into the file first.
 *
 * @p tx_pkt_cnt: number of packet to drop.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_sink_tx,
    TP_ARGS(
        const void*, port,
        uint64_t, tx_pkt_cnt
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint64_t, tx_pkt_cnt, tx_pkt_cnt)
    )
)

/**
 * Flush the sink port.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_sink_flush,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
    )
)

/**
 * Free the sink port.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_sink_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
    )
)

/**
 * Create a source port
 *
 * @p port: pointer to the sink port data structure
 * @p file_name: pcap file name to write to
 * @p n_bytes_per_pkt:  The number of bytes to be read from each packet in the
 *  pcap file. If this value is 0, the whole packet is read.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_source_create,
    TP_ARGS(
        const void*, port,
        struct rte_port_source_params*, params
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_string(pcap_file_name, params->file_name != NULL ? params->file_name : "" )
        ctf_integer(uint32_t, n_bytes_per_pkt, params->n_bytes_per_pkt)
    )
)

/**
 * Receive/read packets from a pcap file
 *
 * @p rx_pkt_cnt: number of received packets.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_source_rx,
    TP_ARGS(
        const void*, port,
        uint32_t, rx_pkt_cnt
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
        ctf_integer(uint32_t, rx_pkt_cnt, rx_pkt_cnt)
    )
)

/**
 * Free the source port.
 */
TRACEPOINT_EVENT(
    librte_port_source_sink,
    rte_port_source_free,
    TP_ARGS(
        const void*, port
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, port, port)
    )
)
#endif /* _RTE_PORT_SOURCE_SINK_TRACE_H */

#include <lttng/tracepoint-event.h>