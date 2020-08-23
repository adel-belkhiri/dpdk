#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_array

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_array_trace.h"

#if !defined(_RTE_TABLE_ARRAY_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_ARRAY_TRACE_H

#include <lttng/tracepoint.h>
#include <smmintrin.h>

#define MAX_BURST_PKT_NUM          64

 /****************************************************************
 ** RTE Table Array
 ** Simple array indexing. Lookup key is the array entry index
 ** which is extracted from packet metadata.
 ****************************************************************/

/**
 * Create an array table
 *
 * @p tbl: Pointer to the table
 * @p offset: Byte offset within input packet meta-data where lookup key (i.e. the
	    array entry index) is located.
 * @p n_entries: Maximum number of the array rules
 * @p entry_size: Uniq rule size
 */
TRACEPOINT_EVENT(
    librte_table_array,
    rte_table_array_create,
    TP_ARGS(
        const void*, tbl,
        uint32_t, entry_size,
        uint32_t, n_entries,
        uint32_t, offset
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, entry_size, entry_size)
        ctf_integer(uint32_t, n_entries, n_entries)
        ctf_integer(uint32_t, offset, offset)
    )
)

/**
 * Free an array table
 */
TRACEPOINT_EVENT(
    librte_table_array,
    rte_table_array_free,
    TP_ARGS(
        const void*, tbl
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
    )
)

/**
 * Add an entry to an array table
 *
 * @p key: position of the rule in the array.
 * @p entry_ptr: pointer to the rule
 * @p key_found: always equal to 1.
 */
TRACEPOINT_EVENT(
    librte_table_array,
    rte_table_array_entry_add,
    TP_ARGS(
        const void*, tbl,
        uint32_t, key,
        const void*, entry_ptr,
        int, key_found
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, key, key)
        ctf_integer_hex(const void*, entry_ptr, entry_ptr)
        ctf_integer(int, key_found, key_found)
    )
)

/**
 * Lookup for matching rules
 *
 * @p n_pkts_in: Number of packets feeded to the lookup function.
 * @p n_pkts_out: Number of matching packets.
 * @p entries: pointers to rules matching packets
 */
 TRACEPOINT_EVENT(
    librte_table_array,
    rte_table_array_lookup,
    TP_ARGS(
        const void*, tbl,
        uint32_t, n_pkts_in,
        uint64_t, lookup_hit_mask,
        void**, entries
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)

        ctf_sequence(void*, entries_ptr,
        ({
            void* array[MAX_BURST_PKT_NUM];
            for(int i = 0; i < n_pkts_in; i++) {
                uint64_t pkt_mask = 1LLU << i;
                if(pkt_mask & lookup_hit_mask)
                    array[i] = entries[i];
                else
                    array[i] = NULL;
            }
            array;
        }), size_t, n_pkts_in)

        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, __builtin_popcountll(lookup_hit_mask))
    )
)

#endif /* _RTE_TABLE_ARRAY_TRACE_H */
#include <lttng/tracepoint-event.h>