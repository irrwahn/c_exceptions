#include <stdio.h>

#include "except.h"

#ifndef USE_NO_EXCEPTIONS_

/*
** make this a thread local object, if required (and if posible at all!):
*/
static ctxbuf_t_ *ctx_top_ = NULL;

void push_ctx_( ctxbuf_t_ *p )
{
	p->e.ex = 0;
	p->e.func = "";
	p->e.file = "";
	p->e.line = 0;
	p->flags = CTX_ST_MUSTPOP_;
    p->next = ctx_top_;
    ctx_top_ = p;
}

ctxbuf_t_ *pop_ctx_( void )
{
    ctxbuf_t_ *p = ctx_top_;
	if ( ctx_top_ != NULL )
		ctx_top_ = p->next;
    return p;
}

void unhandled_ex_( except_t_ e, const char *func, const char *file, int line )
{
	fprintf( stderr, "unhandled exception %d in %s (%s:%d), from %s (%s:%d)\n",
			e.ex, func, file, line, e.func, e.file, e.line );
}


#endif

/* EOF */
