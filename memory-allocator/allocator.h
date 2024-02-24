#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# ifndef TESTER_MODE
#  define TESTER_MODE 0
# endif

# if TESTER_MODE
#  include "tester.h"
#  define ALLOCATE_MEMORY fake_malloc
#  define FREE_MEMORY fake_free
# else
#  define ALLOCATE_MEMORY malloc
#  define FREE_MEMORY free
# endif

/*
	A struct to store memory blocks which allocated
	by using malloc function.

	Yes, it is a linked list.
*/
typedef struct s_memory_block {
	void *ptr;
	struct s_memory_block *next;
} t_memory_block;

void			*safe_malloc(int size);
void			safe_free(void *ptr);
t_memory_block	*get_memory_blocks(void);
void			free_memory(void);
void			abort_memory(void);
void 			register_pre_abort_func(void (*abort_func)(void));
void 			register_post_abort_func(void (*abort_func)(void));

#endif
