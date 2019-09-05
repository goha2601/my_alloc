#include <stdlib.h>
#include <stdio.h>
#include "my_alloc.h"

/* Define pool and block sizes for project.
 * It needs to calculate by user, no checkerrors
 * for uncorrect POOL_SIZE and BLOCK_SIZE
 */

#define POOL_SIZE	1024
#define BLOCK_SIZE	64
/* Thread names */
#define THREAD_1 	1
#define THREAD_2	2

int check_error(int test, int err)
{
	if (err == 0)
		printf("\nTEST%d : OK\n", test);
	else
		printf("\nTEST%d : FAIL\n", test);
}

int main(void)
{
	Pool a;
	arch_type block_cnt = POOL_SIZE / BLOCK_SIZE;
	arch_type mem[block_cnt];
	arch_type *ptr[block_cnt];
	arch_type ea = 0; /* Error accumulator variable */

	printf("Start allocator testing procedure:\n");	
	/* 1. Programm tries to allocate more memory, than Pool has */
	printf("\n1 TEST : Init Pool for %d blocks and trying to take %d blocks\n",\
			block_cnt, block_cnt + 1);
	if(pool_init(&a, mem, POOL_SIZE , BLOCK_SIZE, THREAD_1)){
		printf("Init error\n");
		return 1;
	}
	for (int i = 0; i < block_cnt + 1; i++) {
		ptr[i] = pool_alloc(&a, THREAD_1);
		if (ptr[i] != NULL)
			printf("%d: Addr = %p \n", i, ptr[i]);	
		else{
			ea=0;
			printf("\nReceived NULL, test 1 is OK\n\n");
		}
	}
	for (int i = 0; i < block_cnt; i++) {
		if (pool_free(&a, ptr[i], THREAD_1) != 0){
			ea++;
			printf("Error in free_pool procedure\n");
		}else	
			printf("Free_pool successfully complete, OK\n");
	
	}
	check_error(1,ea);
	ea = 0;

	/* 2. Thread tries to work with foreign pool */
	printf("\n2 TEST : Trying to work with foreign pool\n");
	ptr[0] = pool_alloc(&a, THREAD_2);
	if (ptr[0] = NULL)
		printf("\n%d: Addr = %p   ERROR\n", 0, ptr[0]);	
	else{
		printf("\n%d: Addr = %p \n", 0, ptr[0]);	
		printf("Received NULL, THREAD_2 cann't take memory block\n"
			       "from foreign pool\n");
		printf("\nTEST2 : OK\n");
	}
	
	/* 3. Trying to alloc and freeing blocks */
	printf("\n3 TEST : Trying to alloc and freeing blocks from pool\n\n");
	for (int i = 0; i < block_cnt - 8; i++) {
		ptr[i] = pool_alloc(&a, THREAD_1);
		if (ptr[i] != NULL)
			printf("%d: Addr = %p \n", i, ptr[i]);	
		else
			ea++;	
	}
	for (int i = 0; i < block_cnt - 10; i++) {
		if (pool_free(&a, ptr[i], THREAD_1) != 0) {
			printf("Error in free_pool procedure\n");
			ea++;
		}else	
			printf("Free_pool successfully complete, OK\n");
	
	}
	for (int i = 0; i < block_cnt - 4; i++) {
		ptr[i] = pool_alloc(&a, THREAD_1);
		if (ptr[i] != NULL)
			printf("%d: Addr = %p \n", i, ptr[i]);	
		else
			ea++;
	}
	for (int i = 0; i < block_cnt - 4; i++) {
		if (pool_free(&a, ptr[i], THREAD_1) != 0) {
			printf("Error in free_pool procedure\n");
			ea++;
		}else	
			printf("Free_pool successfully complete, OK\n");
	
	}
	check_error(3, ea);
	/* It's better to make subroutines for tests */
	return 0;
}
