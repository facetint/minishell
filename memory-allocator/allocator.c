/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:13:21 by hamza             #+#    #+#             */
/*   Updated: 2023/12/17 15:22:52 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "allocator.h"
#define GOOD_EXIT 1
#define BAD_EXIT  0

/**
* @brief Global variables are forbidden, so we used
* static variables to implement them.
*
* This function returns head of memory blocks
* list.
*/
t_memory_block	*get_memory_blocks(void)
{
	static t_memory_block	memory_blocks = {NULL, NULL};

	return (&memory_blocks);
}

/**
* @brief This function basically adds new element to
* the our memory blocks list.

* @return
* 	if success, returns 1.
* 	otherwise, returns 0.
*/
int	append_memory_block(void *ptr)
{
	t_memory_block	*memory_blocks;
	t_memory_block	*new;

	if (!ptr)
		return (BAD_EXIT);
	new = ALLOCATE_MEMORY(sizeof(t_memory_block));
	if (!new)
		return (BAD_EXIT);
	*new = (t_memory_block){.ptr = ptr, .next = NULL};
	memory_blocks = get_memory_blocks();
	while (memory_blocks->next != NULL)
		memory_blocks = memory_blocks->next;
	memory_blocks->next = new;
	return (GOOD_EXIT);
}

/**
* @brief This function basically scans memory blocks
* to find pointer given and removes it.
*
* @return
*	if success, returns 1.
* otherwise, returns 0.
*/
int	remove_memory_block(void *ptr)
{
	t_memory_block	*cur; 
	t_memory_block	*prev;

	if (!ptr)
		return (BAD_EXIT);
	cur = get_memory_blocks();
	while (cur != NULL)
	{
		if (cur->ptr == ptr)
		{
			prev->next = cur->next;
			FREE_MEMORY(cur);
			return (GOOD_EXIT);
		}
		prev = cur;
		cur = cur->next;
	}
	return (BAD_EXIT);
}

/**
* @brief Allocates memory block using the malloc function
* which you know.

* However it stores every pointer and track them to
* abort the program gracefully.

* @return
*	if success, returns allocated memory block.
*	otherwise, frees ALL memory blocks and returns null pointer.
*/
void	*safe_malloc(int size)
{
	void	*ptr;

	ptr = ALLOCATE_MEMORY(size);
	if (!ptr)
	{
		abort_memory();
		return (NULL);
	}
	if (!append_memory_block(ptr))
	{
		FREE_MEMORY(ptr);
		abort_memory();
		return (NULL);
	}
	return (ptr);
}

/**
* @brief frees memory block which allocated by using safe_malloc
* function.
*/
void	safe_free(void *ptr)
{
	if (!ptr)
		return;
	remove_memory_block(ptr);
	FREE_MEMORY(ptr);
}
