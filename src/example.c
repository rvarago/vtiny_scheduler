#include "example.h"

static void 
tst1( void* param )
{
	printf( "TST1: %s\n", ( char* ) param );
}

vtiny_scheduler_t scheduler;

void 
signal_handler( int sig_num )
{
	 vtiny_scheduler_execute( &scheduler );
}

int
main( int argc, char** argv )
{
	vtiny_scheduler_initialize( &scheduler );
	if( vtiny_scheduler_append_procedure( &scheduler, tst1, "Foo", 2 ) == -1 )
	{
		exit( -1 );
	}
	if( vtiny_scheduler_append_procedure( &scheduler, tst1, "Bar", 4 ) == -1 )
	{
		exit( -1 );
	}
	signal( 2, signal_handler ); 
	while( 1 ) ;
	return( 0 );
}
