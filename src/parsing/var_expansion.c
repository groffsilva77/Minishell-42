/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/24 12:34:45 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int			g_exit_status = 0;

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
	if (input[start] == '?')
	{
		(*i) += 2;
		value = malloc(12);
		if (!value)
			return (NULL);
		printf("%d\n", g_exit_status);
		return (value);
	}
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
	*i = start + len;
	return (value);
}

char	*expand_tokens(const char *token)
{
	char	*expanded;
	char	*value;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	if (!token)
		return (NULL);
	expanded = malloc(1024);
	if (!expanded)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '$')
		{
			value = expand_var(token, &i);
			if (value)
			{
				while (value[k])
					expanded[j++] = value[k++];
				free(value);
			}
		}
		else
			expanded[j++] = token[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
