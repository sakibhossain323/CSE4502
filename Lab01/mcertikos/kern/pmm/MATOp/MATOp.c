#include <lib/debug.h>
#include "import.h"

#define PAGESIZE     4096
#define VM_USERLO    0x40000000
#define VM_USERHI    0xF0000000
#define VM_USERLO_PI (VM_USERLO / PAGESIZE)
#define VM_USERHI_PI (VM_USERHI / PAGESIZE)

/**
 * Allocate a physical page.
 *
 * 1. First, implement a naive page allocator that scans the allocation table (AT)
 *    using the functions defined in import.h to find the first unallocated page
 *    with normal permissions.
 *    (Q: Do you have to scan the allocation table from index 0? Recall how you have
 *    initialized the table in pmem_init.)
 *    Then mark the page as allocated in the allocation table and return the page
 *    index of the page found. In the case when there is no available page found,
 *    return 0.
 * 2. Optimize the code using memoization so that you do not have to
 *    scan the allocation table from scratch every time.
 */

static unsigned int next_page_index = VM_USERLO_PI;

unsigned int palloc()
{
    // TODO
    unsigned int nps = get_nps();
    if(nps < VM_USERHI_PI) return 0;
    
    if(next_page_index >= VM_USERHI_PI) next_page_index = VM_USERLO_PI;
    unsigned int beginning_index = next_page_index;

    while(1)
    {
        if(at_is_norm(next_page_index) && !at_is_allocated(next_page_index))
        {
            at_set_allocated(next_page_index, 1);
            next_page_index++;
            return next_page_index - 1;
        }

        next_page_index++;
        if(next_page_index >= VM_USERHI_PI) next_page_index = VM_USERLO_PI;
        if(next_page_index == beginning_index) break;
    }


    return 0;
}

/**
 * Free a physical page.
 *
 * This function marks the page with given index as unallocated
 * in the allocation table.
 *
 * Hint: Simple.
 */
void pfree(unsigned int pfree_index)
{
    // TODO
    at_set_allocated(pfree_index, 0);
}
