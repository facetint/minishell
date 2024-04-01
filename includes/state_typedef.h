/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_typedef.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:25:23 by hamza             #+#    #+#             */
/*   Updated: 2024/03/31 09:31:00 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_TYPEDEF_H
# define STATE_TYPEDEF_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;

typedef void				*(*t_lexer_state)(t_token **lexer_data,
				char *input, int *const i);
typedef void				*(*t_parser_state)(t_token **lexer_data,
				t_command *command);

#endif