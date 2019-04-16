// gcc -O3 -march=native -lgc -shared -o mypthread.so mypthread.c

#include <string.h>
#define GC_THREADS
#define GC_PTHREADS
#include <gc.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void * arg)
{
    return GC_pthread_create(thread, attr, start_routine, arg);
}

int pthread_join(pthread_t thread, void **retval)
{
    return GC_pthread_join(thread, retval);
}

int GC_pthread_detach(pthread_t thread)
{
    return GC_pthread_detach(thread);
}

int main()
{
    (void)pthread_create;
    (void)pthread_join;
    (void)GC_pthread_detach;
    return 0;
}