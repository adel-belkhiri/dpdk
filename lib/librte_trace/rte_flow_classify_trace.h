#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_flow_classify

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_flow_classify_trace.h"

#if !defined(_RTE_FLOW_CLASSIFY_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_FLOW_CLASSIFY_TRACE_H

#include <lttng/tracepoint.h>
#include <rte_flow_classify.h>
#include <rte_table_acl.h>

/** 
 * This event is fired when a classifier is created 
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    rte_flow_classifier_create,
    TP_ARGS(
        const char*, cls_name,
        int, socket_id
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
        ctf_integer(int, socket_id, socket_id)
    )
)

/** 
 * This event is fired when a classifier is freed
 *  @p cls_name : classifier name
 * 
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    rte_flow_classifier_free,
    TP_ARGS(
        const char*, cls_name
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
    )
)

/**
 * This event is fired when a table is added to a classifier
 *  @p type : Type of created table (only acl_ipv4_5tuple is supported) { 
 *          - RTE_FLOW_CLASSIFY_TABLE_TYPE_NONE = 1
 *          - RTE_FLOW_CLASSIFY_TABLE_ACL_IP4_5TUPLE = 2, 
 *          - RTE_FLOW_CLASSIFY_TABLE_ACL_VLAN_IP4_5TUPLE = 3,
 *          - RTE_FLOW_CLASSIFY_TABLE_ACL_QINQ_IP4_5TUPLE = 4
 *      }
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    rte_flow_classify_table_create,
    TP_ARGS(
        const char*, cls_name,
        const void*, tbl,
        struct rte_flow_classify_table_params*, params
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
        ctf_string(tbl_name, ((struct rte_table_acl_params*)(params->arg_create))->name)
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint8_t, type, params->type)
       
    )
)

/**
 * This event is fired when a table entry is deleted
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    rte_flow_classify_table_entry_delete,
    TP_ARGS(
        const char*, cls_name,
        const void*, tbl,
        uint8_t, rule_id
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint8_t, rule_id, rule_id)        
    )
)

/**
 * This event is fired when a table entry is added. Up to now, just "acl_ipv4_5tuple" flows
 *  are supported by DPDK.
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    rte_flow_classify_table_entry_add,
    TP_ARGS(
        const char*, cls_name,
        const void*, tbl,
        uint32_t, rule_id,
        const void*, entry_ptr,        
        uint8_t, rule_type,
        int, key_found,
        struct rte_flow_classify_ipv4_5tuple*, tuple
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
        ctf_integer_hex(void*, tbl, tbl)
        ctf_integer(uint32_t, rule_id, rule_id)
        ctf_integer(void*, entry_ptr, entry_ptr)
        ctf_integer(uint8_t, rule_type, rule_type)
        ctf_integer(int, key_found, key_found)

        ctf_integer(uint32_t, dst_ip, tuple->dst_ip)
        ctf_integer(uint32_t, dst_ip_mask, tuple->dst_ip_mask)
        ctf_integer(uint32_t, src_ip, tuple->src_ip)
        ctf_integer(uint32_t, src_ip_mask, tuple->src_ip_mask)
        ctf_integer(uint16_t, dst_port, tuple->dst_port)
        ctf_integer(uint16_t, dst_port_mask, tuple->dst_port_mask)        
        ctf_integer(uint16_t, src_port, tuple->src_port)
        ctf_integer(uint16_t, src_port_mask, tuple->src_port_mask)
        ctf_integer(uint8_t, proto, tuple->proto)
        ctf_integer(uint8_t, proto_mask, tuple->proto_mask)        
    )
)

/**
 * This event is fired when a lookup is initiated. A lookup is initiated when the user call the function
 * "rte_flow_classifier_query" to find packets matching a given "single" flow rule in the table.
 * First, the lookup (function "flow_classifier_lookup") determins all the rules that match input packets and 
 * the "rte_flow_classifier_query" checks if the input rule is among them and, if so, executes its action 
 * part (count number of matching packets).
 */ 
TRACEPOINT_EVENT(
    librte_flow_classify,
    flow_classifier_lookup,
    TP_ARGS(
        const char*, cls_name,
        const void*, tbl,
        uint32_t, n_pkts_in,
        uint32_t, n_pkts_out,
        uint64_t, lookup_hit_mask,
        void**, entries_ptr
    ),
    TP_FIELDS(
        ctf_string(cls_name, cls_name)
        ctf_integer_hex(const void*, tbl, tbl)
        ctf_integer(uint32_t, n_pkts_in, n_pkts_in)
        ctf_integer(uint32_t, n_pkts_out, n_pkts_out)
        ctf_sequence(void*, entries_ptr,
        ({
            void* array[MAX_BURST_PKT_NUM];
            for(int i = 0; i < n_pkts_in; i++) {
                uint64_t pkt_mask = 1LLU << i;
                if(pkt_mask & lookup_hit_mask) 
                    array[i] = entries_ptr[i];
                else
                    array[i] = NULL;
            }    
            array;
        }), size_t, n_pkts_in)
    )
)

#endif /* _RTE_FLOW_CLASSIFY_TRACE_H */
#include <lttng/tracepoint-event.h>