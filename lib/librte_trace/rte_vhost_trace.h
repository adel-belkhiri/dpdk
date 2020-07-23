#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_vhost

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_vhost_trace.h"

#if !defined(_RTE_VHOST_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_VHOST_TRACE_H

#include <lttng/tracepoint.h>
#include <stdbool.h>



TRACEPOINT_EVENT(
    librte_vhost,
    rte_vhost_driver_register,
    TP_ARGS(
        const char*, path,
        bool, is_server,
        uint64_t, flags
    ),
    TP_FIELDS(
        ctf_string(path, path)
        ctf_integer(bool, is_server, is_server)
        ctf_integer(uint64_t, flags, flags)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    rte_vhost_driver_unregister,
    TP_ARGS(
        const char*, path
    ),
    TP_FIELDS(
        ctf_string(path, path)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    rte_vhost_driver_start,
    TP_ARGS(
        const char*, path,
        pthread_t, fdset_tid
    ),
    TP_FIELDS(
        ctf_string(path, path)
        ctf_integer(pthread_t, fdset_tid, fdset_tid)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    vhost_user_add_connection,
    TP_ARGS(
        int, vid,
        int, connfd,
        const char*, ifce_name
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer(int, connfd, connfd)
        ctf_string(ifce_name, ifce_name)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    destroy_device,
    TP_ARGS(
        int, vid
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    alloc_vring_queue,
    TP_ARGS(
        int, vid,
        uint32_t, vring_idx,
        void*, vq
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer(uint32_t, vring_idx, vring_idx)
        ctf_integer_hex(void*, vq, vq)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    set_vring_enabled,
    TP_ARGS(
        int, vid,
        int, vring_idx,        
        void*, vq,
        uint32_t, size,
        int, kickfd,
        int, callfd
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer(int, vring_idx, vring_idx)        
        ctf_integer_hex(void*, vq, vq)
        ctf_integer(uint32_t, size, size)
        ctf_integer(int, kickfd, kickfd)  
        ctf_integer(int, callfd, callfd)
       
    )
)

//tracepoint(librte_vhost, virtio_is_ready, dev->vid, dev->ifname, dev->nr_vring,
// dev->dequeue_zero_copy, dev->vhost_hlen, vq_is_packed(dev), dev->flags);
TRACEPOINT_EVENT(
    librte_vhost,
    virtio_is_ready,
    TP_ARGS(
        int, vid,
        const char*, ifce_name,
        uint32_t, nr_vring,
        int, dequeue_zero_copy,
        uint16_t, vhost_hlen,
        bool, vq_is_packed,
        uint32_t, flags
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_string(ifce_name, ifce_name)
        ctf_integer(uint32_t, nr_vring, nr_vring)
        ctf_integer(int, dequeue_zero_copy, dequeue_zero_copy)
        ctf_integer(uint16_t, vhost_hlen, vhost_hlen)
        ctf_integer(bool, vq_is_packed, vq_is_packed)   
        ctf_integer(uint32_t, flags, flags)       
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    read_from_rx_ring,
    TP_ARGS(
        int, vid,
        void*, vq,
        uint32_t, count,
        uint32_t, nb_rx,
        uint16_t, last_avail_idx,
        uint16_t, avail_idx
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer_hex(void*, vq, vq)
        ctf_integer(uint32_t, count, count)
        ctf_integer(uint32_t, nb_rx, nb_rx)        
        ctf_integer(uint16_t, last_avail_idx, last_avail_idx)
        ctf_integer(uint16_t, avail_idx, avail_idx)
    )
)

TRACEPOINT_EVENT(
    librte_vhost,
    dequeue_burst,
    TP_ARGS(
        int, vid,
        void*, vq,        
        uint16_t, queue_id,
        uint16_t, nb_rx
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer_hex(void*, vq, vq)        
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint16_t, nb_rx, nb_rx)
    )
)

/**
 * Transmission 
 * 
 */
TRACEPOINT_EVENT(
    librte_vhost,
    enqueue_burst,
    TP_ARGS(
        int, vid,
        void*, vq,
        uint16_t, queue_id,
        uint32_t, count,
        uint32_t, nb_tx
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer_hex(void*, vq, vq)        
        ctf_integer(uint16_t, queue_id, queue_id)
        ctf_integer(uint32_t, count, count)
        ctf_integer(uint32_t, nb_tx, nb_tx)
    )
)

/**
 * write_to_tx_ring : Put a number of packet on the tx ring
 * vid : id of the device
 * vq : virtual queue
 * count : nb of packets to transmit
 * nb_tx : nb of packets already transmitted
 * free_slot_in_the_ring = (avail_idx - last_avail_idx)
 * 
 */
TRACEPOINT_EVENT(
    librte_vhost,
    write_to_tx_ring,
    TP_ARGS(
        int, vid,
        void*, vq,
        int, count,
        uint16_t, last_avail_idx,
        uint16_t, avail_idx
    ),
    TP_FIELDS(
        ctf_integer(int, vid, vid)
        ctf_integer_hex(void*, vq, vq)
        ctf_integer(int, count, count)
        ctf_integer(uint16_t, last_avail_idx, last_avail_idx)
        ctf_integer(uint16_t, avail_idx, avail_idx)
    )
)
#endif /* _RTE_VHOST_TRACE_H */

#include <lttng/tracepoint-event.h>
