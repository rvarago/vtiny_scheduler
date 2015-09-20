#include "vtiny_scheduler.h"

void
vtiny_scheduler_initialize( vtiny_scheduler_t* scheduler )
{
	scheduler->index = 0;
}

int
vtiny_scheduler_append_procedure( vtiny_scheduler_t* scheduler, vtiny_scheduler_procedure_t procedure, void* procedure_parameter, int executions )
{
	if( scheduler->index >= VTINY_SCHEDULER_POOL_SIZE )
	{
		return( -1 );
	}	
	scheduler->procedures[ scheduler->index ].procedure = procedure;
	scheduler->procedures[ scheduler->index ].parameter = procedure_parameter;
	scheduler->procedures[ scheduler->index ].executions = executions;
	scheduler->index++;
	return( 0 );
}

int
vtiny_scheduler_execute( vtiny_scheduler_t* scheduler )
{
	static struct
	{
		int last_index;
		int pending;
	} vtiny_executor_sm = { 0, 1 };
	register int i = vtiny_executor_sm.last_index;
	
	for( i = vtiny_executor_sm.last_index; i < scheduler->index || vtiny_executor_sm.pending; i++ )
	{
		if( i == scheduler->index && vtiny_executor_sm.pending )
		{
			i = 0;	
			vtiny_executor_sm.pending = 0;
		}
		if( scheduler->procedures[ i ].executions == VTINY_SCHEDULER_EXECUTE_FOREVER || scheduler->procedures[ i ].executions > 0 )
		{	
			scheduler->procedures[ i ].procedure( scheduler->procedures[ i ].parameter );
			if( scheduler->procedures[ i ].executions > 0 )
			{
				scheduler->procedures[ i ].executions--;
			}
			vtiny_executor_sm.last_index = i + 1;
			vtiny_executor_sm.pending = 1;
			return( 1 );
		}
	}
	return( 0 );
}

