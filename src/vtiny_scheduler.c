/* Copyright [2017] [Rafael Varago]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "vtiny_scheduler.h"

void
vtiny_scheduler_initialize( vtiny_scheduler_t* scheduler )
{
	scheduler->index = 0;
}

int
vtiny_scheduler_append_task( vtiny_scheduler_t* scheduler, vtiny_task_t task, void* task_parameter, int executions )
{
	if( scheduler->index >= VTINY_SCHEDULER_POOL_SIZE )
	{
		return( -1 );
	}	
	scheduler->tasks[ scheduler->index ].task = task;
	scheduler->tasks[ scheduler->index ].parameter = task_parameter;
	scheduler->tasks[ scheduler->index ].executions = executions;
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
	int return_from_task;

	for( i = vtiny_executor_sm.last_index; i < scheduler->index || vtiny_executor_sm.pending; i++ )
	{
		if( i == scheduler->index && vtiny_executor_sm.pending )
		{
			i = 0;	
			vtiny_executor_sm.pending = 0;
		}
		if( scheduler->tasks[ i ].executions == VTINY_SCHEDULER_EXECUTE_FOREVER || scheduler->tasks[ i ].executions > 0 )
		{	
			return_from_task = scheduler->tasks[ i ].task( scheduler->tasks[ i ].parameter );
			if( return_from_task < 0 )
			{
				scheduler->tasks[ i ].executions = 0;
			}
			else if( scheduler->tasks[ i ].executions > 0 )
			{
				scheduler->tasks[ i ].executions--;
				vtiny_executor_sm.last_index = i + 1;
				vtiny_executor_sm.pending = 1;
			}
			return( 1 );
		}
	}
	return( 0 );
}

