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

#include "example.h"

static int 
tst1( void* param )
{
	printf( "Task 1: %s\n", ( char* ) param );
	return( 0 );
}

static int 
tst2( void* param )
{
	printf( "Task 2: %s\n", ( char* ) param );
	return( 0 );
}

int
main( int argc, char** argv )
{
	vtiny_scheduler_t scheduler;
	
	printf( "Started process PID = %d\n", getpid() );
	
	vtiny_scheduler_initialize( &scheduler );
	
	if( vtiny_scheduler_append_task( &scheduler, tst1, "Foo", 2 ) < 0 )
	{
		perror( "Error in task 1" );
		return( -1 );
	}
	if( vtiny_scheduler_append_task( &scheduler, tst2, "Bar", 4 ) < 0 )
	{
		perror( "Error in task 2" );
		return( -1 );
	}
	
	while( vtiny_scheduler_execute( &scheduler ) ) 
	{
		// Left blank
	}

	return( 0 );
}
