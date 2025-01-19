/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/19 16:22:45 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*get_env_value(const char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_var(const char *input, int *i)
{
	int		start;
	int		len;
	char	*var_name;
	char	*value;

	start = *i + 1;
	len = 0;
	while (input[start + len] && (ft_isalnum(input[start + len])
			|| input[start + len] == '_'))
			len++;
	if (len == 0)
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	var_name = ft_strndup(&input[start], len);
	value = get_env_value(var_name);
	free(var_name);
	*i += len;
	return (value);
}

char	*expand_tokens(const char *token)
{
	char	*expanded;
	int		i, j, k;
	char	var_name[256];
	char	*value;

	if (!token)
		return (NULL);
	expanded = malloc(1024);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			k = 0;
			while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
			{
				var_name[k++] = token[i++];
				if (k >= 255)
				{
					var_name[255] = '\0';
					break ;
				}
			}
			var_name[k] = '\0';
			value = getenv(var_name);
			if (value)
			{
				while (*value)
					expanded[j++] = *value++;
			}
		}
		else
			expanded[j++] = token[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
