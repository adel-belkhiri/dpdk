#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_ethdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_ethdev_trace.h"

#if !defined(_RTE_ETHDEV_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_ETHDEV_TRACE_H

#include <lttng/tracepoint.h>

/**
 * The functions exported by the application Ethernet API to setup a device
 * designated by its port identifier must be invoked in the following order:
 *     - rte_eth_dev_configure()
 *     - rte_eth_tx_queue_setup()
 *     - rte_eth_rx_queue_setup()
 *     - rte_eth_dev_start()
 *
 * (For documentation, please read the file rte_ethdev.h )
 */

/**
 * After probing the PCI bus, create an Ethernet device
 * @p port_id: Ethernet device identifier.
 * @p name: Name of the device
 */
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

/**
 * Configure an Ethernet device.
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_configure,
    TP_ARGS(
        uint16_t, port_id,
	const char*, name,
	uint16_t, nb_rx_q,
	uint16_t, nb_tx_q,
	uint64_t, rx_offloads,
	uint64_t, tx_offloads,
	uint32_t, max_rx_pkt_len
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
        ctf_string(name, name)
        ctf_integer(uint16_t, nb_rx_q, nb_rx_q)
        ctf_integer(uint16_t, nb_tx_q, nb_tx_q)
        ctf_integer(uint64_t, rx_offloads, rx_offloads)
        ctf_integer(uint64_t, tx_offloads, tx_offloads)
        ctf_integer(uint32_t, max_rx_pkt_len, max_rx_pkt_len)
    )
)

/**
 * Start an Ethernet device.
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_start,
    TP_ARGS(
        uint16_t, port_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
    )
)

/**
 * Stop an Ethernet device. The device can be restarted with a call to
 * rte_eth_dev_start()
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_stop,
    TP_ARGS(
        uint16_t, port_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
    )
)

/**
 * Link up an Ethernet device.
 *
 * Set device link up will re-enable the device rx/tx
 * functionality after it is previously set device linked down.
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_set_link_up,
    TP_ARGS(
        uint16_t, port_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
    )
)

/**
 * Link down an Ethernet device.
 * The device rx/tx functionality will be disabled if success, and it
 * can be re-enabled with a call to rte_eth_dev_set_link_up()
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_set_link_down,
    TP_ARGS(
        uint16_t, port_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
    )
)

/**
 * Close a stopped Ethernet device. The device cannot be restarted!
 * The resources are free but the port id is kept.
 */
TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_dev_close,
    TP_ARGS(
        uint16_t, port_id
    ),
    TP_FIELDS(
        ctf_integer(uint16_t, port_id, port_id)
    )
)

/**
 * Close the device and free all its resources.
 */
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

/**
 * Allocate and set up a transmit queue for an Ethernet device.
 */
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

/**
 * Allocate and set up a reception queue for an Ethernet device.
 */
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

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_rx_burst,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id,
        uint16_t, nb_rx
    ),
    TP_FIELDS(
        ctf_integer(int, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint16_t, nb_rx, nb_rx)
    )
)

TRACEPOINT_EVENT(
    librte_ethdev,
    rte_eth_tx_burst,
    TP_ARGS(
        uint16_t, port_id,
        uint16_t, queue_id,
        uint16_t, nb_tx
    ),
    TP_FIELDS(
        ctf_integer(int, port_id, port_id)
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint16_t, nb_tx, nb_tx)
    )
)

#endif /* _RTE_ETHDEV_TRACE_H */

#include <lttng/tracepoint-event.h>
