#ifndef _VTINY_SCHEDULER_H_
#define	_VTINY_SCHEDULER_H_

#define	VTINY_SCHEDULER_POOL_SIZE		10
#define	VTINY_SCHEDULER_EXECUTE_FOREVER		-1


/*
**	Procedure function signature.
*/
typedef void( *vtiny_scheduler_procedure_t )( void* parameter );

struct vtiny_scheduler_t_ 
{
	struct
	{
		vtiny_scheduler_procedure_t procedure;
		void* parameter;
		int executions;
	}procedures[ VTINY_SCHEDULER_POOL_SIZE ];
	int index;
};

/*
*	Define a vtiny scheduler type
*/
typedef struct vtiny_scheduler_t_ vtiny_scheduler_t;

void
vtiny_scheduler_initialize( vtiny_scheduler_t* scheduler );

int 
vtiny_scheduler_append_procedure( vtiny_scheduler_t* scheduler, vtiny_scheduler_procedure_t procedure, void* procedure_parameter, int executions );

int
vtiny_scheduler_execute( vtiny_scheduler_t* scheduler ); 

#endif /* _VTINY_SCHEDULER_H_ */

