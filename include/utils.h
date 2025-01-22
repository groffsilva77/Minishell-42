/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:43:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/19 11:45:28 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//functions we will use somewhere (from libft)
char	**split(t_shell *shell, char str, char c);
char	*strdup(t_shell *shell, const char *s1);
char	*strjoin(t_shell *shell, char const *s1, char const *s2);
size_t	strlen(const char *str);
void	*memcpy(void *dest, const void *src, size_t n);

#endif