/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:43:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/28 19:30:54 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
//functions we will use somewhere (from libft)

char	*fts_strdup(t_shell *shell, const char *s1);
char	*fts_strjoin(t_shell *shell, char const *s1, char const *s2);
char    **ft_realloc_array(char **array, int new_size, char *new_value,
        t_shell *shell);

#endif