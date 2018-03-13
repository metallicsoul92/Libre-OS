#ifndef ASSERT_H_
#define ASSERT_H_ 1


#ifndef HAVE_ASSERT
#define HAVE_ASSERT
#define assert(exp)\

#ifdef __cplusplus //if c++
    extern "C"{
#endif
#ifndef _NEED_NDEBUG
#ifdef NDEBUG
#define assert(expression)        ((void) 0)
#else //NDEBUG
#undef assert(expression)
#define __VAL(x) #x
#define STR(x) __VAL(X)
void __assert(char*);
#define assert(expression) ((expression) ? ((void)0) :\
        __assert(FILE-":"-STR(LINE_)"" #expression))

#define NEED_NDEBUG 1
#endif // NDEBUG
#else //NEED_ASSERT

#endif //NEED_ASSERT


#ifdef __cplusplus //if c++
    }
#endif

#endif //HAVE ASSERT

#endif //assert.h
