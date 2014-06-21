#include <stdio.h>
#include <stdlib.h>

#include "except.h"

#define EX_FOO 1
#define EX_BAR 2


static void test1( void )
{
    try_
    {
        printf( "in try 1...\n" );
        throw_( EX_BAR );
        printf( "huh?!?\n" );
    }
    catch_( EX_FOO )
    {
        printf( "caught 'foo' in 1 ...\n" );
    }
    catch_all_
	{
        printf( "1 caught exception %d from %s (%s:%d)...\n",
				exception_ex_(), exception_func_(),
				exception_file_(), exception_line_() );
	}
    final_
	{
        printf( "in final 1.\n" );
	}
    etry_;
}


static void test2( void )
{
    try_
    {
        printf( "in try 2...\n" );
        throw_( EX_FOO );
        printf( "huh?!?\n" );
    }
    catch_( EX_FOO )
    {
        printf( "caught 'foo' in 2 ...\n" );
    }
    final_
	{
        printf( "in final 2.\n" );
	}
    etry_;
}

static void test3( void )
{
    try_
    {
        printf( "in try 3...\n" );
        throw_( EX_BAR );
        printf( "huh?!?\n" );
    }
    catch_( EX_FOO )
    {
        printf( "caught 'foo' in 3 ...\n" );
    }
    catch_all_
	{
        printf( "caught unknown %d ...\n", exception_ex_() );
	}
    etry_;
}

static void test4( void )
{
    try_
    {
        printf( "in try 4...\n" );
        throw_( 222 );
        throw_( EX_BAR );
        printf( "huh?!?\n" );
    }
    catch_( EX_FOO )
    {
        printf( "caught 'foo' in 4 ...\n" );
    }
    final_
	{
        printf( "in final 4.\n" );
	}
    etry_;
}


static void test5( void )
{
    try_
    {
        printf( "in try 5...\n" );
        //throw_( EX_FOO );
        test4();
        printf( "huh?!?\n" );
    }
    catch_( EX_BAR )
    {
        printf( "caught 'bar' in 5 ...\n" );
    }
    final_
	{
        printf( "in final 5.\n" );
	}
    etry_;
}


int main( void )
{
	try_
	{
		test1();
		test2();
		test3();
		//test4();
		test5();
		//throw_(42);
	}
	/*
    catch_all_
	{
        printf( "main caught exception %d from %s (%s:%d)...\n",
				exception_ex_(), exception_func_(),
				exception_file_(), exception_line_() );
	}
	*/
	etry_;
    return 0;
}
