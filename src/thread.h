/* thread.h — the course's threads in two calls.
   Read it once; you never need to memorise it.

   thread_t t = thread_start(cook, 3);   a new cook walks into the kitchen and runs cook(3)
   thread_join(t);                       wait here until that cook is finished

   A cook is an ordinary function that takes one int:   void cook(int k) { ... }  */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef pthread_t thread_t;            /* the cook's ticket, like a pid */
struct box { void (*fn)(int); int arg; };      /* what a new cook is handed */

static void *trampoline(void *p) {     /* the new cook's first steps */
    struct box b = *(struct box *)p;   /* open the box ...           */
    free(p);                           /* ... throw it away ...      */
    b.fn(b.arg);                       /* ... and go cook            */
    return NULL;
}
static inline thread_t thread_start(void (*fn)(int), int arg) {
    struct box *b = malloc(sizeof *b); /* a box of the cook's own: a value, not an address */
    thread_t t;
    if (b != NULL) { b->fn = fn; b->arg = arg; }
    if (b == NULL || pthread_create(&t, NULL, trampoline, b) != 0) {
        fputs("thread_start: could not start a cook\n", stderr);
        exit(EXIT_FAILURE);
    }
    return t;
}
static inline void thread_join(thread_t t) { pthread_join(t, NULL); }   /* wait for that cook */
