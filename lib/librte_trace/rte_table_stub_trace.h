#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_stub

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_stub_trace.h"

#if !defined(_RTE_TABLE_STUB_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_STUB_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_table_stub.h>


#define MAX_BURST_PKT_NUM          64

/**
 * Create an LPM table
 *
 * @p stub: pointer to the stub table
 */
TRACEPOINT_EVENT(
    librte_table_stub,
    rte_table_stub_create,
    TP_ARGS(
        const void*, tbl
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
    )
)

/**
 * Stub Lookup.
 *
 * @p tbl: pointer to the stub table
 * @p n_pkts_in: number of packets concerned with the lookup
 */
TRACEPOINT_EVENT(
    librte_table_stub,
    rte_table_stub_lookup,
    TP_ARGS(
        const void*, tbl,
        uint32_t, n_pkts_in
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
    )
)

#endif /* _RTE_TABLE_LPM_TRACE_H */
#include <lttng/tracepoint-event.h>