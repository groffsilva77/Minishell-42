/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:28:28 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/19 11:54:40 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strjoin(t_shell *shell, char const *s1, char const *s2)
{
    char    *join;
    size_t  len1;
    size_t  len2;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    join = ft_malloc(shell, len1 + len2 + 1);
    if (!join)
        return (NULL);
    ft_memcpy(join, s1, len1);
    ft_memcpy(join + len1, s2, len2 + 1);
    return (join);
}