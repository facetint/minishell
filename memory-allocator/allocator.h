/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:17:28 by hamza             #+#    #+#             */
/*   Updated: 2024/03/25 15:20:02 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H

/*
	A struct to store memory blocks which allocated
	by using malloc function.

	Yes, it is a linked list.
*/
typedef struct s_memory_block
{
	void					*ptr;
	struct s_memory_block	*next;
}	t_memory_block;

void			*safe_malloc(int size);
void			safe_free(void *ptr);
t_memory_block	*get_memory_blocks(void);
void			free_memory(void);
void			abort_memory(void);
void			register_pre_abort_func(void (*abort_func)(void));
void			register_post_abort_func(void (*abort_func)(void));

#endif
