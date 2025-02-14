/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:59:29 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/14 15:53:04 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

char	*get_env_value(const char *var)
{
	char	*value;

	if (!var)
		return (ft_strdup(""));
	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	if (ft_strcmp(var, "PATH") == 0)
	{
		printf("%s\n", value);
		return (ft_strdup(""));
	}
	else
	{
		printf("%s\n", value);
		return (ft_strdup(""));
	}
	return (ft_strdup(value));
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

char	*expand_var(const char *input, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*value;

	start = *i + 1;
	len = 0;
	if (input[start] == '?')
	{
		*i += 2;
		return (ft_itoa(g_exit_status));
	}
	while (input[start + len] && (ft_isalnum(input[start + len])
			|| input[start + len] == '_'))
			len++;
	if (len == 0)
		return ((*i)++, ft_strdup("$"));
	var_name = malloc(len + 1);
	ft_strlcpy(var_name, &input[start], len + 1);
	value = get_env_value(var_name);
	free(var_name);
	*i = start + len;
	return (value);
}

int	expand_variable(const char *token, size_t *i, char *expanded, int j)
{
	char	*value;
	int		k;

	value = expand_var(token, i);
	if (!value)
		return (j);
	k = 0;
	if (value)
	{
		while (value[k])
			expanded[j++] = value[k++];
	}
	return (j);
}

char	*process_expansion(const char *token, char *expanded,
			size_t max_len, int allow_expansion)
{
	size_t	i;
	size_t	j;
	int		in_quotes[2];

	i = 0;
	j = 0;
	in_quotes[0] = 0;
	in_quotes[1] = 0;
	while (token[i] && j < max_len - 1)
	{
		if (handle_quotes_state(token[i], &in_quotes[0], &in_quotes[1]))
			i++;
		else if (token[i] == '$' && allow_expansion && !in_quotes[0])
			j = expand_variable(token, &i, expanded, j);
		else
			expanded[j++] = token[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
