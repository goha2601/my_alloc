#include "my_alloc.h"


/* Allocate a chunk from the pool. */
void *pool_alloc(Pool* buf, arch_type thread_id)
{
	if(!buf)
		return NULL;

	if(!buf->head)
		return NULL; 

	if(buf->thread_id != thread_id)
		return NULL;

	arch_type* curr_ptr = buf->head;
	buf->head = (*((arch_type**)(buf->head)));
	return curr_ptr;
}


/* Return block to the pool. Be carefull, if you'll return more than you've taken, you can miss head of pool */
int pool_free(Pool* buf, void* ptr, arch_type thread_id)
{
	if(!buf || !ptr)
		return 1;

	if(buf->thread_id != thread_id)
		return 1;

	*((arch_type**)ptr) = buf->head;
	buf->head = (arch_type*)ptr;
	return 0;
}


/* Initialise the pool header structure, and set all chunks in the pool as empty. */
int pool_init(Pool* buf, arch_type* mem, arch_type size, arch_type chunk_size, arch_type thread_id)
{
	if(!buf || !mem || !size || !chunk_size)
		return 1;

	const arch_type chunk_count = (size / chunk_size) - 1;

	for(arch_type chunk_index = 0; chunk_index < chunk_count; ++chunk_index) {

		arch_type *curr_chunk = mem + (chunk_index * chunk_size);
		*((arch_type**)curr_chunk) = curr_chunk + chunk_size;
	}

	*((arch_type**)&mem[chunk_count * chunk_size]) = NULL; /* terminating NULL */
	buf->mem = buf->head = mem;
	buf->thread_id = thread_id;
	return 0;
}
