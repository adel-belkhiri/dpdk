#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_eventdev

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_eventdev_trace.h"

#if !defined(_RTE_EVENTDEV_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EVENTDEV_TRACE_H

#include <lttng/tracepoint.h>
#include "rte_eventdev_header_trace.h"
#include <rte_eventdev.h>
#include <rte_event_eth_rx_adapter.h>


/**
 * Create an event device
 *
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_pmd_allocate,
    TP_ARGS(
        int, socket_id,
        const char*, name,
        uint8_t, dev_id,
        void*, eventdev
    ),
    TP_FIELDS(
        ctf_integer(int, socket_id, socket_id)
        ctf_string(name, name)
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer_hex(void*, eventdev, eventdev)
    )
)

/**
 * Configure an eventdev device
 * @p dev_id:
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_dev_configure,
    TP_ARGS(
        void*, eventdev,
        uint8_t, dev_id,
        const struct rte_event_dev_config*, dev_conf
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, eventdev, eventdev)
        ctf_integer(uint8_t, dev_id, dev_id)

        ctf_integer(uint32_t, dequeue_timeout_ns, dev_conf->dequeue_timeout_ns)
        ctf_integer(int32_t, nb_events_limit, dev_conf->nb_events_limit)
        ctf_integer(uint8_t, nb_event_queues, dev_conf->nb_event_queues)
        ctf_integer(uint8_t, nb_event_ports, dev_conf->nb_event_ports)
        ctf_integer(uint32_t, nb_event_queue_flows, dev_conf->nb_event_queue_flows)
        ctf_integer(uint32_t, nb_event_port_dequeue_depth, dev_conf->nb_event_port_dequeue_depth)
        ctf_integer(uint32_t, nb_event_port_enqueue_depth, dev_conf->nb_event_port_enqueue_depth)
    )
)

/**
 * Allocate and set up an event queue for an event device.
 *
 * @p dev_id:
 * @p queue_id:
 * @p nb_atomic_flows:
 * @p nb_atomic_order_sequences:
 * @p event_queue_cfg:
 * @p schedule_type:
 *          - RTE_SCHED_TYPE_ORDERED : 0
 *          - RTE_SCHED_TYPE_ATOMIC  : 1
 *          - RTE_SCHED_TYPE_PARALLEL : 2
 * @p priority:
 * @p ret:
*/
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_queue_setup,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, queue_id,
        const struct rte_event_queue_conf*, queue_conf,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, queue_id, queue_id)

        ctf_integer(uint32_t, nb_atomic_flows, queue_conf->nb_atomic_flows)
        ctf_integer(uint32_t, nb_atomic_order_sequences, queue_conf->nb_atomic_order_sequences)
        ctf_integer(uint32_t, event_queue_cfg, queue_conf->event_queue_cfg)
        ctf_integer(uint8_t, schedule_type, queue_conf->schedule_type)
        ctf_integer(uint8_t, priority, queue_conf->priority)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Allocate and set up an event port for an event device.
 *
 * @p dev_id: event device id
 * @p port_id: port id
 * @p new_event_threshold: A backpressure threshold for new event enqueues on this port.
 *      Use for *closed system* event dev where event capacity is limited,
 *      and cannot exceed the capacity of the event dev.
 * @p dequeue_depth: Configure number of bulk dequeues for this event port.
 * @p enqueue_depth: Configure number of bulk enqueues for this event port.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_port_setup,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, port_id,
        const struct rte_event_port_conf*, port_conf,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_integer(int32_t, new_event_threshold, port_conf->new_event_threshold)
        ctf_integer(uint8_t, disable_implicit_release, port_conf->disable_implicit_release)
        ctf_integer(uint16_t, dequeue_depth, port_conf->dequeue_depth)
        ctf_integer(uint16_t, enqueue_depth, port_conf->enqueue_depth)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Link multiple source event queues supplied in *queues* to the destination
 * event port designated by its *port_id* with associated service priority
 * supplied in *priorities* on the event device designated by its *dev_id*.
 *
 * @p dev_id:
 * @p port_id:
 * @p queues: List of queues links to this port.
 * @p priorities: List of priorities associated to the aforementioned queues.
 * @p nb_links: number of linked queues
 * @p ret: indicates the number of links that are actually established.
 *         The return value can be less than the value of the *nb_links*
 *         parameter when the implementation has the limitation on specific
 *         queue to port link establishment.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_port_link,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, port_id,
        const uint8_t*, queues,
        const uint8_t*, priorities,
        const uint16_t, nb_links,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_sequence(uint8_t, queues, queues, size_t, nb_links)
        ctf_sequence(uint8_t, priorities, priorities, size_t, nb_links)
        ctf_integer(uint16_t, nb_links, nb_links)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Unlink multiple source event queues supplied in *queues* from the destination
 * event port designated by its *port_id* on the event device designated
 * by its *dev_id*.
 * @p dev_id:
 * @p port_id:
 * @p queues:
 * @p nb_unlinks:
 * @p ret:
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_port_unlink,
    TP_ARGS(
        uint8_t, dev_id,
        uint8_t, port_id,
        const uint8_t*, queues,
        const uint16_t, nb_unlinks,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(uint8_t, port_id, port_id)

        ctf_sequence(uint8_t, queues, queues, size_t, nb_unlinks)
        ctf_integer(uint16_t, nb_unlinks, nb_unlinks)
        ctf_integer(int, ret, ret)
    )
)

/**
 *  Start an event device.
 *
 * The device start step is the last one and consists of setting the event
 * queues to start accepting the events and schedules to event ports.
 *
 * On success, all basic functions exported by the API (event enqueue,
 * event dequeue and so on) can be invoked.
 *
 * @p dev_id:
 * @p ret:
 *  *   0: Success, device started.
 *      -ESTALE : Not all ports of the device are configured
 *      -ENOLINK: Not all queues are linked, which could lead to deadlock.
 */

TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_dev_start,
    TP_ARGS(
        uint8_t, dev_id,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Stop an event device.
 *
 * This function causes all queued events to be drained, including those
 * residing in event ports. While draining events out of the device, this
 * function calls the user-provided flush callback (if one was registered) once
 * per event.
 *
 * @p dev_id:
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_dev_stop,
    TP_ARGS(
        uint8_t, dev_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
    )
)

/**
 * Close an event device. The device cannot be restarted!
 *
 * @p dev_id: Event device identifier
 * @p ret:
*    - 0 on successfully closing device
*    - <0 on failure to close device
*    - (-EAGAIN) if device is busy
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_dev_close,
    TP_ARGS(
        uint8_t, dev_id,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Create an event device
 *
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_pmd_release,
    TP_ARGS(
        void*, eventdev
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, eventdev, eventdev)
    )
)

/**
 * ##file : rte_event_eth_rx_adapter.c##
 * rte_event_eth_rx_adapter_create
 *
 * @p rxa_id: RX adapter id
 * @p dev_id: event device id
 * @p conf_cb:
 * Function type used for adapter configuration callback. The callback is
 * used to fill in members of the struct rte_event_eth_rx_adapter_conf, this
 * callback is invoked when creating a SW service for packet transfer from
 * ethdev queues to the event device.
 *
 */

TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_rx_adapter_create,
    TP_ARGS(
        uint8_t, rxa_id,
        uint8_t, dev_id,
        const void*, conf_cb
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, rxa_id, rxa_id)
        ctf_integer(uint8_t, dev_id, dev_id)
        ctf_integer(const void*, conf_cbet, conf_cb)
    )
)

/**
 * Free the event_eth_rx_adapter
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_rx_adapter_free,
    TP_ARGS(
        uint8_t, rxa_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, rxa_id, rxa_id)
    )
)

/**
 * Add a receive queue to an event adapter.
 *
 * @p rxa_id: rx_adapter identifier
 * @p eth_dev_id: Ethernet device index
 * @p rx_queue_id: Ethernet device queue index. If rx_queue_id is -1,
 *  then all Rx queues configured for the device are added. If the ethdev
 *  Rx queues can only be connected to a single event queue then rx_queue_id is
 *  required to be -1.
 *
 * @p rx_queue_flags: Flags for handling received packets
 * @p servicing_weight: Relative polling frequency of ethernet receive queue when the
 *         adapter uses a service core function for ethernet to event device transfers.
 *         If it is set to zero, the Rx queue is interrupt driven
 *
 * Important: The SW service is created within the
 * rte_event_eth_rx_adapter_queue_add() function if SW based packet transfers
 * from ethdev queues to the event device are required.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_rx_adapter_queue_add,
    TP_ARGS(
        uint8_t, rxa_id,
        uint16_t, eth_dev_id,
        int32_t, queue_id,
        const struct rte_event_eth_rx_adapter_queue_conf*, queue_conf
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, rxa_id, rxa_id)
        ctf_integer(uint16_t, eth_dev_id, eth_dev_id)
        ctf_integer(int32_t, queue_id, queue_id)

        ctf_integer(uint32_t, queue_flags, queue_conf->rx_queue_flags)
        ctf_integer(uint32_t, servicing_weight, queue_conf->servicing_weight)
    )
)

/**
 * Delete a receive queue from an event adapter.
 *
 * @p rxa_id: Adapter identifier.
 * @p eth_dev_id: Port identifier of Ethernet device.
 * @p rx_queue_id: Ethernet device receive queue index. If rx_queue_id is -1,
 *                 then all Rx queues configured for the device are deleted.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_rx_adapter_queue_del,
    TP_ARGS(
        uint8_t, rxa_id,
        uint16_t, eth_dev_id,
        int32_t, rx_queue_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, rxa_id, rxa_id)
        ctf_integer(uint16_t, eth_dev_id, eth_dev_id)
        ctf_integer(int32_t, rx_queue_id, rx_queue_id)
    )
)

/**
 * Controle (start/stop) the RX adapter.
 *
 * @p rxa_id:
 * @p start: if start ==1 then the adapter is started, otherwise it is stopped (start==0).
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rxa_ctrl,
    TP_ARGS(
        uint8_t, rxa_id,
        int, start
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, rxa_id, rxa_id)
        ctf_integer(int, start, start)
    )
)

/**
 * ##file : rte_event_eth_tx_adapter.c##
 * rte_event_eth_tx_adapter_create
 *
 * @p rxa_id: TX adapter id
 * @p dev_id: event device id
 */

TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_create,
    TP_ARGS(
        uint8_t, txa_id,
        uint8_t, dev_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
        ctf_integer(uint8_t, dev_id, dev_id)
    )
)

/**
 * Free the event_eth_tx_adapter
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_free,
    TP_ARGS(
        uint8_t, txa_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
    )
)

/**
 * Add a TX queue to a txa adapter
 *
 * @p txa_id:
 * @p eth_dev_id:
 * @p queue_id: Ethernet device queue index. If rx_queue_id is -1,
 *  then all Tx queues configured for the device are added.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_queue_add,
    TP_ARGS(
        uint8_t, txa_id,
        uint16_t, eth_dev_id,
        int32_t, queue_id,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
        ctf_integer(uint16_t, eth_dev_id, eth_dev_id)
        ctf_integer(int32_t, queue_id, queue_id)
        ctf_integer(int, ret, ret)
    )
)

/**
 * Delete a TX queue from a txa adapter
 *
 * @p txa_id:
 * @p eth_dev_id:
 * @p queue_id: id of the queue added to this adapter. A queue value of -1 is used to indicate all
 * queues within the device, that have been added to this
 * adapter.
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_queue_del,
    TP_ARGS(
        uint8_t, txa_id,
        uint16_t, eth_dev_id,
        int32_t, queue_id,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
        ctf_integer(uint16_t, eth_dev_id, eth_dev_id)
        ctf_integer(int32_t, queue_id, queue_id)
        ctf_integer(int, ret, ret)
    )
)


/**
 * Start a tx adapter
 *
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_start,
    TP_ARGS(
        uint8_t, txa_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
    )
)

/**
 * Stop a tx adapter
 *
 */
TRACEPOINT_EVENT(
    librte_eventdev,
    rte_event_eth_tx_adapter_stop,
    TP_ARGS(
        uint8_t, txa_id
    ),
    TP_FIELDS(
        ctf_integer(uint8_t, txa_id, txa_id)
    )
)
#endif /* _RTE_EVENTDEV_TRACE_H */
#include <lttng/tracepoint-event.h>