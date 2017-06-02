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

#ifndef _VTINY_SCHEDULER_H_
#define	_VTINY_SCHEDULER_H_

#define	VTINY_SCHEDULER_POOL_SIZE		10
#define	VTINY_SCHEDULER_EXECUTE_FOREVER		-1

/**************************************************************
* Module types and redefinitions
**************************************************************/

/* 
* @brief The vtiny task signature, all tasks needs to agree it.
*/
typedef int( *vtiny_task_t )( void* parameter );

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

/* 
* @brief  The vtiny initializer, use it before any vtiny function call. 
*/ 
void
vtiny_scheduler_initialize( vtiny_scheduler_t* scheduler );

/* 
* @brief Insert new task to scheduler 
*/
int 
vtiny_scheduler_append_task( vtiny_scheduler_t* scheduler, vtiny_task_t task, void* task_parameter, int executions );

/* 
* @brief Run this and pass task's executions to vtiny 
*/
int
vtiny_scheduler_execute( vtiny_scheduler_t* scheduler ); 

#endif /* _VTINY_SCHEDULER_H_ */

