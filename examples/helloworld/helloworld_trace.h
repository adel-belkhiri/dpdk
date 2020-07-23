#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER dpdk

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./helloworld_trace.h"

#if !defined(_HELLOWORLD_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _HELLOWORLD_TRACE_H

#include <lttng/tracepoint.h>


TRACEPOINT_EVENT(
    dpdk,
    test,
    TP_ARGS(
        int, lcoreid
    ),
    TP_FIELDS(
        ctf_integer(int, lcoreid, lcoreid)
    )
)

#endif /* _HELLOWORLD_TRACE_H */

#include <lttng/tracepoint-event.h>
