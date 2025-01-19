/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:39:00 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/19 11:41:10 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

//functions we will use to manage memory
void	*ft_malloc(t_shell *shell, size_t size);
void	ft_free(t_shell *shell, void *ptr);
void	ft_free_all(t_shell *shell);

#endif