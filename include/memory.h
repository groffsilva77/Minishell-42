/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:39:00 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/28 18:37:21 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

#include "minishell.h"
#include "parsing.h"
//functions we will use to manage memory
void	*ft_malloc(t_shell *shell, size_t size);
void	ft_free(t_shell *shell, void *ptr);
void	ft_free_all(t_shell *shell);
void	free_commands(t_command *commands, t_shell *shell);

#endif