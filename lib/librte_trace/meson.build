# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2017 Intel Corporation

version = 2
sources = files('rte_trace.c')
headers = files('rte_lpm_trace.h',
				'rte_vhost_trace.h',
				'rte_ethdev_trace.h',
				'rte_eal_trace.h',
				'rte_eth_vhost_trace.h')
				
# since header files have different names, we can install all vector headers
# without worrying about which architecture we actually need

lttng_ust_dep = dependency('lttng-ust', required: false)
if lttng_ust_dep.found()
		ext_deps += lttng_ust_dep
endif