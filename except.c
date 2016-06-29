#include <stdio.h>

#include "except.h"

#ifndef DISABLE_EXCEPTIONS_

/*
 * Make the exception context stack a thread local object if requested.
 * Requires C11 thread or POSIX threads support to be available.
 */
#ifdef ENABLE_THREAD_EXCEPTIONS_
 #include <pthread.h>
 #ifdef _PTHREAD_H
  // use POSIX threads
  #define THREAD_LOCAL_	 __thread
 #elif ( __STDC_VERSION__ >= 201112L ) && !defined __STDC_NO_THREADS__
  // use C11 threads
  #include <thread.h>
  #define THREAD_LOCAL_  thread_local
 #else
  #error "Thread local storage support not available!"
  #define THREAD_LOCAL_
 #endif
#else
 #define THREAD_LOCAL_
#endif

static THREAD_LOCAL_ except_ctx_t_ *ctx_top_ = NULL;

#undef THREAD_LOCAL_

void push_ex_ctx_( except_ctx_t_ *p )
{
	p->e.ex = 0;
	p->e.func = "";
	p->e.file = "";
	p->e.line = 0;
	p->flags = CTX_ST_MUSTPOP_;
    p->next = ctx_top_;
    ctx_top_ = p;
}

except_ctx_t_ *pop_ex_ctx_( void )
{
    except_ctx_t_ *p = ctx_top_;
	if ( ctx_top_ != NULL )
		ctx_top_ = p->next;
    return p;
}

void unhandled_ex_( except_t_ e, const char *func, const char *file, int line )
{
	fprintf( stderr, "unhandled exception %d in '%s' (%s:%d), from '%s' (%s:%d): ",
			e.ex, func, file, line, e.func, e.file, e.line );
}


#endif //ndef DISABLE_EXCEPTIONS_

/* EOF */
