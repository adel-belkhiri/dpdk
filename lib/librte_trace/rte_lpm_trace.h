#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_lpm

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_lpm_trace.h"

#if !defined(_RTE_LPM_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_LPM_TRACE_H

#include <lttng/tracepoint.h>
#include <smmintrin.h>

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_create,
    TP_ARGS(
        const void*, lpm,
        const char*, name,
        uint32_t, max_rules,
        uint32_t, number_tbl8s
    ),
    TP_FIELDS(
        ctf_integer_hex(const void*, lpm, lpm)
        ctf_string(name, name)
        ctf_integer(uint32_t, max_rules, max_rules)
        ctf_integer(uint32_t, number_tlb8s, number_tbl8s)
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_free,
    TP_ARGS(
        const void*, lpm
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_add,
    TP_ARGS(
        const void*, lpm,
        uint32_t, ipv4,
        uint8_t, depth,
        uint32_t, next_hop
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
        ctf_integer(uint32_t, ipv4, ipv4)
        ctf_integer(uint8_t, depth, depth)
        ctf_integer(uint32_t, next_hop, next_hop)
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_lookup,
    TP_ARGS(
        const void*, lpm,
        uint32_t, ipv4,
        uint32_t, next_hop,
        uint32_t, rule_depth,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
        ctf_integer(uint32_t, ipv4, ipv4)
        ctf_integer(uint32_t, next_hop, next_hop)
        ctf_integer(uint32_t, rule_depth, rule_depth)
        ctf_integer(int, ret, ret)        
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_lookup_bulk,
    TP_ARGS(
        const void*, lpm,
        const uint32_t*, ips,
        const uint32_t*, tbl_entries,
        unsigned int, n
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
        ctf_sequence(uint32_t, ips, ips, size_t, n)
        ctf_sequence(uint32_t, tbl_entries, tbl_entries, size_t, n)
        ctf_integer(unsigned int, n, n)        
    )
)

/**
 * P.S.: rule_depth is declared "ctf_sequence" to sidestep a bug in tracecompass related to 
 * parsing "ctf_array" fields.
 */ 
TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_lookupx4,
    TP_ARGS(
        const void*, lpm,
        __m128i , ips,
        uint32_t*, next_hops,
        uint32_t, defv,
        uint32_t*, tbl_entries
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
        ctf_array(uint32_t, ips,
        ({
            uint32_t vec[4];

            vec[0] = _mm_extract_epi32(ips, 0);
            vec[1] = _mm_extract_epi32(ips, 1);
            vec[2] = _mm_extract_epi32(ips, 2);
            vec[3] = _mm_extract_epi32(ips, 3);
            
            vec;
        }), 4)
        ctf_array(uint32_t, next_hops, next_hops, 4)
        ctf_integer(uint32_t, defv, defv)
        ctf_sequence(uint32_t, rule_depth,
        ({
            uint32_t vec[4];

            vec[0] = ((uint32_t)tbl_entries[0] & 0xFC000000)>>26;
            vec[1] = ((uint32_t)tbl_entries[1] & 0xFC000000)>>26;
            vec[2] = ((uint32_t)tbl_entries[2] & 0xFC000000)>>26;
            vec[3] = ((uint32_t)tbl_entries[3] & 0xFC000000)>>26;

            vec;
        }), size_t, 4)   
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_delete,
    TP_ARGS(
        const void*, lpm,
        uint32_t, ipv4,
        uint8_t, depth,
        int, ret
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
        ctf_integer(uint32_t, ipv4, ipv4)
        ctf_integer(uint8_t, depth, depth)
        ctf_integer(int, ret, ret)
    )
)

TRACEPOINT_EVENT(
    librte_lpm,
    rte_lpm_delete_all,
    TP_ARGS(
        const void*, lpm
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, lpm, lpm)
    )
)

#endif /* _RTE_LPM_TRACE_H */

#include <lttng/tracepoint-event.h>