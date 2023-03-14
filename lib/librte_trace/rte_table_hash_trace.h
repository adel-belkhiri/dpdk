#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_hash

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_hash_trace.h"

#if !defined(_RTE_TABLE_HASH_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_HASH_TRACE_H

#include <lttng/tracepoint.h>

#define MAX_BURST_PKT_NUM          64

/**
 * Create a hash cuckoo table
 *
 *  @p tbl: Pointer to table data structure
 *  @p name: Name of the table
 *  @p n_keys: Capacity of the table in terms of number of rules.
 *  @p key_size: Size of the key
 *  @p entry_size:
 *  @p f_hash: Pointer to the hash function
 *  @p seed: Seed provided to the hash function to compute the key
 *  @p key_offset:
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_create,
    TP_ARGS(
        const void*, tbl,
        const char*, name,
        uint32_t, n_keys,
        uint32_t, key_size,
        uint32_t, entry_size,
        const void*, f_hash,
        uint32_t, seed,
        uint8_t, key_offset
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_string(name, name)
        ctf_integer(uint32_t, n_keys, n_keys)
        ctf_integer(uint32_t, key_size, key_size)
        ctf_integer(uint32_t, entry_size, entry_size)
        ctf_integer_hex(void*, f_hash, f_hash)
        ctf_integer(uint32_t, seed, seed)
        ctf_integer(uint8_t, key_offset, key_offset)
    )
)

/**
 * Delete a hash cuckoo table
 *
 * @p tbl: table pointer
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_free,
    TP_ARGS(
        const void*, tbl
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
    )
)

/**
 * Add an entry to a hash cuckoo table
 *  @p entry_ptr: Pointer to the address memory where the rule is saved.
 *      It is used as an ID of the hash rule.
 *  @p key: Pointer to the data structure containing the key. The hash function is applied to this key
 *      to generate a "hash value" that can be used during rules lookups.
 *  @p key_found: Indicates whether the same key exists already in the table or not.
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_entry_add,
    TP_ARGS(
        const void*, tbl,
        const void*, key,
        int*, key_found,
        void **, entry_ptr

    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, key_found, *key_found)
        ctf_integer_hex(void*, entry_ptr, *entry_ptr)
    )
)

/**
 * Delete an entry from a hash cuckoo table
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_entry_delete,
    TP_ARGS(
        const void*, tbl,
        const void*, key,
        const void*, entry_ptr
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer_hex(const void*, key, key)
        ctf_integer_hex(const void*, entry_ptr, entry_ptr)
    )
)

/**
 * Hash lookup
 *
 *  @p tbl: pointer to the table
 *  @p n_pkts_in: number of packets concerned with the lookup
 *  @p n_pkts_out: number of matching packets
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_lookup,
    TP_ARGS(
        const void*, tbl,
        void**, entries,
        uint64_t, pkts_out_mask,
        uint32_t, n_pkts_in,
        uint32_t, n_pkts_out
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_sequence(void*, entries_ptr,
        ({
            void* array[MAX_BURST_PKT_NUM];
            for(int i = 0; i < n_pkts_in; i++) {
                uint64_t pkt_mask = 1LLU << i;
                if(pkt_mask & pkts_out_mask)
                    array[i] = entries[i];
                else
                    array[i] = NULL;
            }
            array;
        }), size_t, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out)
    )
)
#endif /* _RTE_TABLE_HASH_TRACE_H */
#include <lttng/tracepoint-event.h>
