#ifndef _VTINY_SCHEDULER_H_
#define	_VTINY_SCHEDULER_H_

#define	VTINY_SCHEDULER_POOL_SIZE		10
#define	VTINY_SCHEDULER_EXECUTE_FOREVER		-1

/**************************************************************
* Module types and redefinitions
**************************************************************/

/* The vtiny task signature, all tasks needs to agree it. */
typedef void( *vtiny_task_t )( void* parameter );

/* Internal structure of the vtiny, don't use it's attributes directly */
struct vtiny_scheduler_t_ 
{
	struct
	{
		vtiny_task_t task;
		void* parameter;
		int executions;
	}tasks[ VTINY_SCHEDULER_POOL_SIZE ];
	int index;
};

typedef struct vtiny_scheduler_t_ vtiny_scheduler_t;

/**************************************************************
* Module API
**************************************************************/

/* The vtiny initializer, use it before any vtiny function call. */ 
void
vtiny_scheduler_initialize( vtiny_scheduler_t* scheduler );

/* Insert new task to scheduler */
int 
vtiny_scheduler_append_task( vtiny_scheduler_t* scheduler, vtiny_task_t task, void* task_parameter, int executions );

/* Run this and pass task's executions to vtiny */
int
vtiny_scheduler_execute( vtiny_scheduler_t* scheduler ); 

#endif /* _VTINY_SCHEDULER_H_ */

