#define TRACEPOINT_CREATE_PROBES
#define TRACEPOINT_DEFINE

#include "rte_eal_trace.h"
//#include "rte_ring_trace.h"

#include "rte_lpm_trace.h"
#include "rte_hash_trace.h"
#include "rte_acl_trace.h"

#include "rte_table_lpm_trace.h"
#include "rte_table_hash_trace.h"
#include "rte_table_acl_trace.h"
#include "rte_table_stub_trace.h"

#include "rte_flow_classify_trace.h"

#include "rte_eth_vhost_trace.h"
#include "rte_table_array_trace.h"
#include "rte_pipeline_trace.h"
#include "rte_port_ring_trace.h"
#include "rte_port_ethdev_trace.h"
#include "rte_port_source_sink_trace.h"
#include "rte_port_sym_crypto_trace.h"

#include "rte_ethdev_trace.h"
#include "rte_vhost_trace.h"
#include "rte_cryptodev_trace.h"
#include "rte_eventdev_trace.h"
#include "rte_event_sw_trace.h"
#include "rte_event_dsw_trace.h"
#include "rte_event_ring_trace.h"