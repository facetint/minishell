/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aborter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:14:08 by hamza             #+#    #+#             */
/*   Updated: 2023/12/17 13:46:15 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"
#include <stdlib.h>

/**
* @brief frees all memory blocks which allocated by using safe_malloc
* function but does not call abort functions.
*/
void free_memory(void)
{
	t_memory_block	*memory_blocks;
	t_memory_block	*next;

	memory_blocks = get_memory_blocks()->next;
	while (memory_blocks != NULL)
	{
		next = memory_blocks->next;
		FREE_MEMORY(memory_blocks->ptr);
		FREE_MEMORY(memory_blocks);
		memory_blocks = next;
	}
	get_memory_blocks()->next = NULL;
}

/**
* @brief frees all memory blocks which allocated by using safe_malloc
* function and calls abort functions.
*/
void	abort_memory(void)
{
	register_pre_abort_func(NULL);
	free_memory();
	register_post_abort_func(NULL);
}

/**
* @brief registers abort function to call before when abort_memory
* function is called.
*/
void	register_pre_abort_func(void (*abort_func)(void))
{
	static void	(*func)(void) = NULL;

	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}

/**
* @brief registers abort function to call after when abort_memory
* function is called.
*/
void	register_post_abort_func(void (*abort_func)(void))
{
	static void	(*func)(void) = NULL;

	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}
