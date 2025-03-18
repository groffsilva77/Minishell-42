/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_the_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:54:26 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/18 13:57:35 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes_helper(const char *str, char *result, size_t len)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = stduplicater[i];
			else if (quote == str[i])
				quote = 0;
			else
				result[j++] = str[i];
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
}

char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	remove_quotes_helper(str, result, len);
	return (result);
}


static char *expand_token_value(t_token *tokens, t_shell *shell)
{
	if (tokens->in_single_quotes)
		return ft_strdup(tokens->value);
	else
		return expand_tokens(shell, tokens->value, 1);
}

static int add_argument_to_command(t_command **atl_cmd,
				char *clean_value, t_shell *shell)
{
	char **temp;

	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1, 
			clean_value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free_commands(*atl_cmd);
		*atl_cmd = NULL;
		return (-1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->argument_count++;
	return (0);
}
int handle_arg(t_command **atl_cmd, t_token *tokens, t_shell *shell)
{
	char *expanded_value;
	char *clean_value;

	if (!*atl_cmd)
	{
		*atl_cmd = create_command();
		if (!*atl_cmd)
			return (-1);
	}
	expanded_value = expand_token_value(tokens, shell);
	if (!expanded_value)
	{
		*atl_cmd = NULL;
		return (free_commands(*atl_cmd), -1);
	}
	clean_value = remove_quotes(expanded_value);
	free(expanded_value);
	if (!clean_value)
	{
		*atl_cmd = NULL;
		return (free_commands(*atl_cmd), -1);
	}
	if (add_argument_to_command(atl_cmd, clean_value, shell) == -1)
		return (free(clean_value), -1);
	return (free(clean_value), 0);
}