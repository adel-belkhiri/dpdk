#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_knidev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_kni_trace.h"

#if !defined(_RTE_KNI_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_KNI_TRACE_H

#include <lttng/tracepoint.h>


/**
 * After probing the PCI bus, create an Ethernet device
 * @p port_id: Ethernet device identifier.
 * @p name: Name of the device
*/
TRACEPOINT_EVENT(
    librte_knidev,
    rte_knidev_create,
    TP_ARGS(
        const void*, kni,
        const char*, name
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, kni, kni)
        ctf_string(name, name)
    )
)

 /** @p nb_pkts: Number of packets to rx by the device
 *   @p rx_pkt_cnt: Actual number of objects really rx
 */
TRACEPOINT_EVENT(
    librte_knidev,
    rte_kni_rx_burst,
    TP_ARGS(
        const void*, kni,
        uint32_t, nb_pkts,
        uint32_t, rx_pkt_cnt
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, kni, kni)
        ctf_integer(uint32_t, nb_pkts, nb_pkts)
        ctf_integer(uint32_t, rx_pkt_cnt, rx_pkt_cnt)
    )
)

 /** @p nb_pkts: Number of packets to tx by the device
 *   @p rx_pkt_cnt: Actual number of objects really tx
 */
TRACEPOINT_EVENT(
    librte_knidev,
    rte_kni_tx_burst,
    TP_ARGS(
        const void*, kni,
        uint32_t, nb_pkts,
        uint32_t, tx_pkt_cnt
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, kni, kni)
        ctf_integer(uint32_t, nb_pkts, nb_pkts)
        ctf_integer(uint32_t, tx_pkt_cnt, tx_pkt_cnt)
    )
)

/**
 * Release a Kni device.
 */
TRACEPOINT_EVENT(
    librte_knidev,
    rte_kni_release,
    TP_ARGS(
        const void*, kni
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, kni, kni)
	)
)



#endif /* _RTE_KNI_TRACE_H */

#include <lttng/tracepoint-event.h>
