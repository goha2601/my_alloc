#ifndef _MY_ALLOC_H
#define _MY_ALLOC_H

#include <stdint.h>
#include <stddef.h>

/* Pointer size for target platform, here is 32 or more.
 * Also is important note, that segment size shouldn't
 * be less than pointer size on current architecture.
 * For example for 32-bit architecture  BLOCK_SIZE should be more than 32-bit.
 */
typedef uint32_t arch_type; 

/* Pool structure */
typedef struct {
	arch_type *head;	/* Head of pool pointer */
	arch_type *mem;		/* Constant pointer to the start of pool*/ 
	arch_type thread_id;	/* For multithreading support */
} Pool; 

/* NOTE: One thread uses it's own pool, if you need to work with several threads,
 * please create pools for each one.
 */

/* Init function */
int pool_init(Pool* buf, arch_type* mem, arch_type size, arch_type chunk_size, arch_type thread_id); 

/* Pool chunk allocator subroutine */
void *pool_alloc(Pool* buf, arch_type thread_id); 

/* Freeing mem */
int pool_free(Pool* buf, void* ptr, arch_type thread_id);

#endif /* _MY_ALLOC_H */
