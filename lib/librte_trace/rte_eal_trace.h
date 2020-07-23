#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER librte_eal

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./rte_eal_trace.h"

#if !defined(_RTE_EAL_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _RTE_EAL_TRACE_H

#include <lttng/tracepoint.h>


/*******************************************/
/*                Alarm                    */
/*******************************************/

/* Indicates that an alarm was set */
TRACEPOINT_EVENT(
    librte_eal,
    alarm_set,
    TP_ARGS(
        uint64_t, us,
        void*, cb,
        void*, arg
    ),
    TP_FIELDS(
        ctf_integer(uint64_t, us, us)
        ctf_integer_hex(void*, cb, cb)
        ctf_integer_hex(void*, arg, arg)
    )
)

/* Indicates that an alarm was cancelled */
TRACEPOINT_EVENT(
    librte_eal,
    alarm_cancel,
    TP_ARGS(
        void*, cb,
        void*, arg,
        int, count,
        int, err
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, cb, cb)
        ctf_integer_hex(void*, arg, arg)
        ctf_integer(int, count, count)
        ctf_integer(int, err, err)
    )
)

/******************************************/
/*          Threads tracepoints           */
/******************************************/

/**
 * This event indicates that a task was sent to a slave lcore.
 */
TRACEPOINT_EVENT(
    librte_eal,
    thread_remote_launch,
    TP_ARGS(
        void*, f,
        void*, arg,
        unsigned int, lcore_id,
        int, rc
    ),
    TP_FIELDS(
        ctf_integer_hex(void*, f, f)
        ctf_integer_hex(void*, arg, arg)
        ctf_integer(unsigned int, lcore_id, lcore_id)
        ctf_integer(int, rc, rc)
    )
)


/**
 * This event indicates that an lcore (either master or slave) becomes ready to receive tasks.
 */
TRACEPOINT_EVENT(
    librte_eal,
    thread_lcore_ready,
    TP_ARGS(
        unsigned int, lcore_id,
        uint8_t, master,
        const char*, cpuset
    ),
    TP_FIELDS(
        ctf_integer(unsigned int, lcore_id, lcore_id)
        ctf_integer(uint8_t, master, master)
        ctf_string(cpuset, cpuset)
    )
)

/**
 * An lcore starts the execution of a task.
 */
TRACEPOINT_EVENT(
    librte_eal,
    thread_lcore_running,
    TP_ARGS(
        unsigned int, lcore_id,
        void*, f,
        void*, arg
    ),
    TP_FIELDS(
        ctf_integer(unsigned int, lcore_id, lcore_id)
        ctf_integer_hex(void*, f, f)
        ctf_integer_hex(void*, arg, arg)        
    )
)

/**
 * An lcore finished the execution of a task.
 * State of an lcore.
 * enum rte_lcore_state_t {
 *	WAIT,       < waiting a new command >
 *	RUNNING,    < executing command >
 *	FINISHED,   < command executed >
 * }; 
 */
TRACEPOINT_EVENT(
    librte_eal,
    thread_lcore_waiting,
    TP_ARGS(
        unsigned int, lcore_id,
        int, ret,
        uint8_t, status
    ),
    TP_FIELDS(
        ctf_integer(unsigned int, lcore_id, lcore_id)
        ctf_integer(int, ret, ret)        
        ctf_integer(uint8_t, status, status)
    )
)


/******************************************/
/*          Services tracepoints          */
/******************************************/
/**
 * Indicates the registration of a service 
 */
TRACEPOINT_EVENT(
    librte_eal,
    service_component_register,
    TP_ARGS(
        int32_t, id,
        const char*, service_name,
        void*, cb,
        void*, arg
    ),
    TP_FIELDS(
        ctf_integer(int32_t, id, id)        
        ctf_string(service_name, service_name)
        ctf_integer_hex(void*, cb, cb)    
        ctf_integer_hex(void*, arg, arg)    
    )
)

/**
 * Indicates that a service was unregistred
 */
TRACEPOINT_EVENT(
    librte_eal,
    service_component_unregister,
    TP_ARGS(
        int32_t, id,        
        const char*, service_name

    ),
    TP_FIELDS(
        ctf_integer(int32_t, id, id)        
        ctf_string(service_name, service_name)  
    )
)

/**
 * Indicates that a service started running
 */ 
TRACEPOINT_EVENT(
    librte_eal,
    service_run_begin,
    TP_ARGS(
        int32_t, id,
        int32_t, lcore_id     
    ),
    TP_FIELDS(
        ctf_integer(int32_t, id, id)        
        ctf_integer(int32_t, lcore_id, lcore_id)  
    )
)

/**
 * Indicates that a service started waiting to run again
 */ 
TRACEPOINT_EVENT(
    librte_eal,
    service_run_end,
    TP_ARGS(
        int32_t, id,
        int32_t, lcore_id     
    ),
    TP_FIELDS(
        ctf_integer(int32_t, id, id)        
        ctf_integer(int32_t, lcore_id, lcore_id)  
    )
)

/**
 * Map a service to an lcore
 */
TRACEPOINT_EVENT(
    librte_eal,
    service_map_lcore,
    TP_ARGS(
        int32_t, id,
        int32_t, lcore_id,
        uint32_t, enabled
    ),
    TP_FIELDS(
        ctf_integer(int32_t, id, id)        
        ctf_integer(int32_t, lcore_id, lcore_id)  
        ctf_integer(int32_t, enabled, enabled)                
    )
)

/**
 * Indicates a change in the role of an lcore
 * 
 *  ROLE_RTE <= 0
 *	ROLE_OFF <= 1
 *	ROLE_SERVICE <= 2
 */
TRACEPOINT_EVENT(
    librte_eal,
    lcore_role_change,
    TP_ARGS(
        int32_t, lcore_id,
        uint32_t, lcore_role  
    ),
    TP_FIELDS(  
        ctf_integer(int32_t, lcore_id, lcore_id)  
        ctf_integer(int32_t, lcore_role, lcore_role)                 
    )
)


/**
 * lcore started being ready to run services
 */
TRACEPOINT_EVENT(
    librte_eal,
    service_lcore_ready,
    TP_ARGS(
        int32_t, lcore_id 
    ),
    TP_FIELDS(  
        ctf_integer(int32_t, lcore_id, lcore_id)                  
    )
)

/**
 * The lcore is no longer a SERVICE lcore
 */
TRACEPOINT_EVENT(
    librte_eal,
    service_lcore_stop,
    TP_ARGS(
        int32_t, lcore_id
    ),
    TP_FIELDS(  
        ctf_integer(int32_t, lcore_id, lcore_id)                 
    )
)
#endif /* _RTE_EAL_COMMON_TRACE_H */

#include <lttng/tracepoint-event.h>
