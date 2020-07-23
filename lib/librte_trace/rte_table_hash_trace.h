#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_hash

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_hash_trace.h"

#if !defined(_RTE_TABLE_HASH_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_HASH_TRACE_H

#include <lttng/tracepoint.h>

/**
 * Create a hash cuckoo table
 *      @p tbl : Pointer to table data structure
 *      @p name : name of the table
 *      @p n_keys : 
 *      @p key_size :
 *      @p entry_size :
 *      @p f_hash :
 *      @p seed : 
 *      @p key_offset :
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
 * @p tbl : table pointer
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
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_entry_add,
    TP_ARGS(
        const void*, tbl,
        const void*, key,
        const void*, entry,        
        int*, key_found,
        void **, entry_ptr

    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer_hex(const void*, key, key)
        ctf_integer_hex(const void*, entry, entry)
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
        const void*, key
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer_hex(const void*, key, key)
    )
)

/**
 * Hash lookup
 *      @p tbl : pointer to the table
 *      @p n_pkts_in : number of packets concerned with the lookup
 *      @p n_pkts_out : number of matching packets
 */
TRACEPOINT_EVENT(
    librte_table_hash,
    rte_table_hash_cuckoo_lookup,
    TP_ARGS(
        const void*, tbl,
        uint32_t, n_pkts_in,
        uint32_t, n_pkts_out        
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out)   
    )
)
#endif /* _RTE_TABLE_HASH_TRACE_H */
#include <lttng/tracepoint-event.h>