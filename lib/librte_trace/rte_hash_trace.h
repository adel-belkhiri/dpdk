#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_hash

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_hash_trace.h"

#if !defined(_RTE_HASH_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_HASH_TRACE_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_create,
    TP_ARGS(
        const char*, name,
        uint32_t, max_entries,
        uint32_t, key_len,
        const void*, hash_func,
        uint32_t, hash_func_init_val,
        uint8_t, flags
    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer(uint32_t, max_entries, max_entries)
        ctf_integer(uint32_t, key_len, key_len)
        ctf_integer_hex(void*, hash_func, hash_func)
        ctf_integer(uint32_t, hash_func_init_val, hash_func_init_val)
        ctf_integer(uint8_t, flags, flags) 
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_free,
    TP_ARGS(
        const char*, name
    ),
    TP_FIELDS(
        ctf_string(name, name)
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_add_key,
    TP_ARGS(
        const char*, name,
        const void*, key,
        uint32_t, sig,
        int32_t, ret

    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, sig, sig)
        ctf_integer(int32_t, ret, ret)
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_add_key_with_data,
    TP_ARGS(
        const char*, name,
        const void*, key,
        uint32_t, sig,
        const void*, data,
        int, ret

    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, sig, sig)
        ctf_integer_hex(const void*, data, data)
        ctf_integer(int, ret, ret)
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_del_key,
    TP_ARGS(
        const char*, name,
        const void*, key,
        uint32_t, sig,
        int, ret

    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, sig, sig)
        ctf_integer(int, ret, ret)
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_lookup_key,
    TP_ARGS(
        const char*, name,
        const void*, key,
        uint32_t, sig,
        int, pos

    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, sig, sig)
        ctf_integer(int, pos, pos)
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_lookup_key_with_data,
    TP_ARGS(
        const char*, name,
        const void*, key,
        uint32_t, sig,
        void**, data,
        int, pos

    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer_hex(const void*, key, key)
        ctf_integer(uint32_t, sig, sig)
        ctf_integer(void**, data, data)
        ctf_integer(int, pos, pos)        
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_lookup_bulk,
    TP_ARGS(
        const char*, name,
        const void**, keys,
        uint32_t, num_keys,
        uint32_t*, hashs,               
        int32_t*, positions,
        uint64_t, hit_mask
    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_sequence(void*, keys, keys, uint32_t, num_keys)
        ctf_integer(uint32_t, num_keys, num_keys)
        ctf_sequence(uint32_t, hashs, hashs, uint32_t, num_keys)
        ctf_sequence(void*, positions, positions, uint32_t, num_keys)
        ctf_integer(uint64_t, hit_mask, hit_mask)      
    )
)

TRACEPOINT_EVENT(
    librte_hash,
    rte_hash_free_key_with_position,
    TP_ARGS(
        const char*, name,
        const int32_t, position
    ),
    TP_FIELDS(
        ctf_string(name, name)
        ctf_integer(const int32_t, position, position)
    )
)

#endif /* _RTE_HASH_TRACE_H */

#include <lttng/tracepoint-event.h>