# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2017 Intel Corporation

version = 2
#trace_inc = [global_inc]
sources = files('rte_trace.c')
headers = files('rte_acl_trace.h',
                'rte_cryptodev_trace.h',
                'rte_eventdev_header_trace.h',
                'rte_eventdev_trace.h',
                'rte_event_dsw_trace.h',
                'rte_event_ring_trace.h',
                'rte_event_sw_trace.h',
                'rte_flow_classify_trace.h',
                'rte_hash_trace.h',
                'rte_lpm_trace.h',
                'rte_pipeline_trace.h',
                'rte_port_ethdev_trace.h',
                'rte_port_ring_trace.h',
                'rte_port_source_sink_trace.h',
                'rte_port_sym_crypto_trace.h',
                'rte_ring_trace.h',
                'rte_table_array_trace.h',
                'rte_table_hash_trace.h',
                'rte_table_lpm_trace.h',
                'rte_table_stub_trace.h',
                'rte_vhost_trace.h',
				'rte_ethdev_trace.h',
				'rte_eal_trace.h',
				'rte_eth_vhost_trace.h',
				'rte_spinlock_trace.h',
				'rte_kni_trace.h',
                )

# since header files have different names, we can install all vector headers
# without worrying about which architecture we actually need

lttng_ust_dep = dependency('lttng-ust', required: false)
if lttng_ust_dep.found()
		ext_deps += lttng_ust_dep
endif
