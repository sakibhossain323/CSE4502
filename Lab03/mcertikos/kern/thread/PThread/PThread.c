#include <lib/x86.h>
#include <lib/thread.h>

#include "import.h"

void thread_init(unsigned int mbi_addr)
{
    tqueue_init(mbi_addr);
    set_curid(0);
    tcb_set_state(0, TSTATE_RUN);
}

/**
 * Allocates a new child thread context, sets the state of the new child thread
 * to ready, and pushes it to the ready queue.
 * It returns the child thread id.
 */
unsigned int thread_spawn(void *entry, unsigned int id, unsigned int quota)
{
    // TODO
    unsigned int child = kctx_new(entry, id, quota);
    tcb_set_state(child, TSTATE_READY);
    tqueue_enqueue(NUM_IDS, child);
    return child;
}

/**
 * Yield to the next thread in the ready queue.
 * You should set the currently running thread state as ready,
 * and push it back to the ready queue.
 * Then set the state of the popped thread as running, set the
 * current thread id, and switch to the new kernel context.
 * Hint: If you are the only thread that is ready to run,
 * do you need to switch to yourself?
 */
void thread_yield(void)
{
    // TODO
    // get currently running thread
    int cur = get_curid(); 
    // set to ready state
    tcb_set_state(cur, TSTATE_READY);
    // push to ready queue 
    tqueue_enqueue(NUM_IDS, cur);
    // get next thread
    unsigned int next = tqueue_dequeue(NUM_IDS);
    // set to running state
    tcb_set_state(next, TSTATE_RUN);
    // set current thread id
    set_curid(next);
    // switch to new kernel context
    kctx_switch(cur, next);
}
