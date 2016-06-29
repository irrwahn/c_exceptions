#ifndef INCLUDED_EXCEPT_H
#define INCLUDED_EXCEPT_H

#include <stdlib.h>
#include <setjmp.h>


#ifndef DISABLE_EXCEPTIONS_

typedef struct EXCEPT_STRUCT_ {
    const char *func;
    const char *file;
    int line;
    unsigned short ex;
} except_t_;

typedef struct EXCEPT_CTX_STRUCT_ {
	except_t_ e;
    unsigned short flags;
    struct EXCEPT_CTX_STRUCT_ *next;
    jmp_buf jbuf;
} except_ctx_t_;


extern void push_ex_ctx_( except_ctx_t_ *p );
extern except_ctx_t_ *pop_ex_ctx_( void );
extern void unhandled_ex_( except_t_ e, const char *func, const char *file, int line );


#define CTX_ST_MUSTPOP_   	1
#define CTX_ST_EXHANDLED_	2


#define exception_func_()  	( ctxbuf_.e.func )
#define exception_file_()  	( ctxbuf_.e.file )
#define exception_line_()  	( ctxbuf_.e.line )
#define exception_ex_()  	( ctxbuf_.e.ex )


#define throw_(E) \
	do { \
		except_ctx_t_ *ctx_p_ = pop_ex_ctx_(); \
		if ( NULL == ctx_p_ ) { \
			unhandled_ex_( ctxbuf_.e, __func__, __FILE__, __LINE__ ); \
			abort(); \
		} \
		ctx_p_->e.ex = (E); \
		ctx_p_->e.func = __func__; \
		ctx_p_->e.file = __FILE__; \
		ctx_p_->e.line = __LINE__; \
		ctx_p_->flags &= ~CTX_ST_MUSTPOP_; \
		longjmp( ctx_p_->jbuf, ctx_p_->e.ex ); \
	} while ( 0 )


#define rethrow_() \
	do { \
		except_ctx_t_ *ctx_p_ = pop_ex_ctx_(); \
		if ( NULL == ctx_p_ ) { \
			unhandled_ex_( ctxbuf_.e, __func__, __FILE__, __LINE__ ); \
			abort(); \
		} \
		ctx_p_->e = ctxbuf_.e; \
		ctx_p_->flags &= ~CTX_ST_MUSTPOP_; \
		longjmp( ctx_p_->jbuf, ctx_p_->e.ex ); \
	} while ( 0 )


#define try_ \
    do { \
        except_ctx_t_ ctxbuf_; \
        push_ex_ctx_( &ctxbuf_ ); \
        switch ( setjmp( ctxbuf_.jbuf ) ) \
        { \
        case 0: \


#define catch_(x) \
            break; \
        case x: \
            ctxbuf_.flags |= CTX_ST_EXHANDLED_;


#define catch_all_ \
            break; \
        default: \
            ctxbuf_.flags |= CTX_ST_EXHANDLED_;


#define final_ \
        } \
        if ( 1 ) { \
            if ( ctxbuf_.flags & CTX_ST_MUSTPOP_ ) { \
                pop_ex_ctx_(); \
                ctxbuf_.flags &= ~CTX_ST_MUSTPOP_; \
            }


#define etry_ \
        } \
        if ( ctxbuf_.flags & CTX_ST_MUSTPOP_ ) \
            pop_ex_ctx_(); \
        if ( ctxbuf_.e.ex && !( ctxbuf_.flags & CTX_ST_EXHANDLED_ ) ) \
			rethrow_(); \
    } while ( 0 )


#else //def DISABLE_EXCEPTIONS_

#define exception_()  	(0)
#define throw_(e) 		((void)0)
#define try_ 			do { if ( 1 ) {
#define catch_(x) 		} if ( 0 ) {
#define catch_all_ 		} if ( 0 ) {
#define final_			} if ( 1 ) {
#define etry_ 			} } while ( 0 )

#define exception_func_()  	("")
#define exception_file_()  	("")
#define exception_line_()  	(0)
#define exception_ex_()  	(0)

#endif //ndef DISABLE_EXCEPTIONS_

#endif //ndef INCLUDED_EXCEPT_H
