# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2017 Intel Corporation

# meson file, for building this example as part of a main DPDK build.
#
# To build this example as a standalone application with an already-installed
# DPDK instance, use 'make'

sources = files(
	'main.c',
	'helloworld_trace.c'
)

headers = files(
	'helloworld_trace.h'
)

lttng_ust_dep = dependency('lttng-ust', required: false)
if lttng_ust_dep.found()
		ext_deps += lttng_ust_dep
endif
