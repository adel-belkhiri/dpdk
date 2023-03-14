#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_spinlock

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_spinlock_trace.h"

#if !defined (__SPINLOCK_TRACE_H___) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __SPINLOCK_TRACE_H___

#include <lttng/tracepoint.h>

#if defined(__PPC__) && !defined(__PPC64__)
#define LTTNG_UST_CALLER_IP()           NULL
#else
#define LTTNG_UST_CALLER_IP()           __builtin_return_address(0)
#endif

#define MAX_LCORE_COUNT 512

/**
 * @brief
 *
 */
TRACEPOINT_EVENT(
    librte_spinlock,
    lock_init,
    TP_ARGS(
        void*, sl
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sl, sl)
    )
)

/**
 * @brief
 *
 */
TRACEPOINT_EVENT(
    librte_spinlock,
    lock_req,
    TP_ARGS(
        void*, sl,
        unsigned int, lcore,
        void*, ip
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sl, sl)
        ctf_integer(unsigned int, lcore, (lcore > MAX_LCORE_COUNT)? 0 : lcore)
        ctf_integer_hex(void*, ip, ip)
    )
)


/**
 * @brief
 */
TRACEPOINT_EVENT(
    librte_spinlock,
    lock_acq,
    TP_ARGS(
        void*, sl,
        unsigned int, lcore,
        void*, ip
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sl, sl)
        ctf_integer(unsigned int, lcore, (lcore > MAX_LCORE_COUNT)? 0 : lcore)
        ctf_integer_hex(void*, ip, ip)
    )
)


/**
 * @brief
 *
 */
TRACEPOINT_EVENT(
    librte_spinlock,
    lock_release,
    TP_ARGS(
        void*, sl,
        unsigned int, lcore
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, sl, sl)
        ctf_integer(unsigned int, lcore, (lcore > MAX_LCORE_COUNT)? 0 : lcore)
    )
)

#endif /* __RTE_SPINLOCK_TRACE_H__ */
#include <lttng/tracepoint-event.h>
