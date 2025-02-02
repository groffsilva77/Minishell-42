/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/02 15:14:10 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int			g_exit_status = 0;

char	*get_env_value(const char *var)
{
	char	*value;

	if (ft_strcmp(var, "PATH") == 0)
	{
		value = getenv(var);
		if (value)
		{
			printf("%s\n", value);
			return (ft_strdup(""));
		}
	}
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
		return (printf("%d\n", g_exit_status), value);
	}
	while (input[start + len] && (ft_isalnum(input[start + len])
			|| input[start + len] == '_'))
			len++;
	if (len == 0)
		return ((*i)++, ft_strdup("$"));
	var_name = ft_strndup(&input[start], len);
	value = get_env_value(var_name);
	free(var_name);
	*i = start + len;
	return (value);
}

int	handle_quotes_state(char c, int	*in_squotes, int *in_dquotes)
{
	if (c == '\'' && !(*in_dquotes))
	{
		*in_squotes = !(*in_squotes);
		return (1);
	}
	else if (c == '"' && !(*in_squotes))
	{
		*in_dquotes = !(*in_dquotes);
		return (1);
	}
	return (0);
}

int	expand_variable(const char *token, int *i, char *expanded, int j)
{
	char	*value;
	int		k;

	value = expand_var(token, i);
	if (value)
	{
		k = 0;
		while (value[k])
			expanded[j++] = value[k++];
		free(value);
	}
	return (j);
}

char	*expand_tokens(const char *token, int allow_expansion)
{
	char	*expanded;
	int		i;
	int		j;
	int		in_squotes;
	int		in_dquotes;

	if (!token)
		return (NULL);
	expanded = malloc(ft_strlen(token) * 2 + 1);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	in_squotes = 0;
	in_dquotes = 0;
	while (token[i])
	{
		if (handle_quotes_state(token[i], &in_squotes, &in_dquotes))
			i++;
		else if (token[i] == '$' && allow_expansion && !in_squotes)
			j = expand_variable(token, &i, expanded, j);
		else
			expanded[j++] = token[i++];
	}
	return (expanded[j] = '\0', expanded);
}
