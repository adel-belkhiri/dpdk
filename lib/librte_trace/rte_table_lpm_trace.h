#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_table_lpm

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_table_lpm_trace.h"

#if !defined(_RTE_TABLE_LPM_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_TABLE_LPM_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_table_lpm.h>


#define MAX_BURST_PKT_NUM          64

/** 
 * Create an LPM table
 */
TRACEPOINT_EVENT(
    librte_table_lpm,
    rte_table_lpm_create,
    TP_ARGS(
        const void*, tbl,
        const struct rte_table_lpm_params*, p,
        uint32_t, entry_size,
        const void*, lpm
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_string(name, p->name)
        ctf_integer(uint32_t, max_rules, p->n_rules)
        ctf_integer(uint32_t, number_tlb8s, p->number_tbl8s)
        ctf_integer(int, flags, p->flags)
        ctf_integer(uint32_t, entry_unique_size, p->entry_unique_size)
        ctf_integer(uint32_t, entry_size, entry_size)
        ctf_integer_hex(const void*, lpm, lpm)
    )
)

/*
 *  Delete the LPM table 
 */
TRACEPOINT_EVENT(
    librte_table_lpm,
    rte_table_lpm_free,
    TP_ARGS(
        const void*, tbl
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
    )
)

 /** 
  * Add an entry to the LPM table
  */
TRACEPOINT_EVENT(
    librte_table_lpm,
    rte_table_lpm_entry_add,
    TP_ARGS(
        const void*, tbl,
        const struct rte_table_lpm_key*, key,
        int, key_found,
        uint32_t, nht_pos,        
        const void*, entry_ptr
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer(uint32_t, ip, key->ip)
        ctf_integer(uint8_t, depth, key->depth)
        ctf_integer(int, key_found, key_found)
        ctf_integer(uint32_t, nht_pos, nht_pos)        
        ctf_integer(void*, entry_ptr, entry_ptr)
    )
)

 /**
  * Delete an entry from the LPM table
  */
TRACEPOINT_EVENT(
    librte_table_lpm,
    rte_table_lpm_entry_delete,
    TP_ARGS(
        const void*, tbl,
        const struct rte_table_lpm_key*, key,
        const void*, entry_ptr,
        uint32_t, nht_pos
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer(uint32_t, ip, key->ip)
        ctf_integer(uint8_t, depth, key->depth)
        ctf_integer(void*, entry_ptr, entry_ptr)
        ctf_integer(uint32_t, nht_pos, nht_pos)   
    )
)

/**
 * LPM Lookup 
 * **pkts : array of mbuff to search for their corresponding lpm entries
 * n_pkts_in : number of packets concerned with the lookup
 * n_pkts_out : number of packets to which a corresponding match was found
 */ 
TRACEPOINT_EVENT(
    librte_table_lpm,
    rte_table_lpm_lookup,
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
                    array[i] = entries [i];
                else
                    array[i] = NULL;
            }    
            array;
        }), size_t, n_pkts_in)      
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out)   
    )
)

#endif /* _RTE_TABLE_LPM_TRACE_H */
#include <lttng/tracepoint-event.h>