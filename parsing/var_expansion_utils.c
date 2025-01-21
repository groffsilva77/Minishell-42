/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:50:59 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/21 16:39:23 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "test.h"

// char	init_empty_str(void)
// {
// 	char	*str;

// 	str = malloc(1024);
// 	if (str)
// 		str[0] = '\0';
// 	return (str);
// }

// char	is_valid_var_char(char c)
// {
// 	return (ft_isalnum(c) || c == '_');
// }

// char	*append_string(char *result, const char *value)
// {
// 	if (!value)
// 		return (result);
// 	ft_strncat(result, value, 1024 - ft_strlen(result) - 1);
// 	return (result);
// }

// char	*append_char(char *result, char c)
// {
// 	int	len;

// 	len = ft_strlen(result);
// 	if (len < 1023)
// 	{
// 		result[len] = c;
// 		result[len + 1] = '\0';
// 	}
// 	return (result);
// }

// char	*extract_var_name(const char *token, int *i)
// {
// 	char	var_name[256];
// 	int		j;

// 	j = 0;
// 	while (is_valid_var_char(token[*i]))
// 	{
// 		var_name[j++] = token[*i];
// 		(*i)++;
// 	}
// 	var_name[j] = '\0';
// 	(*i)--;
// 	return (ft_strdup(var_name));
// }
