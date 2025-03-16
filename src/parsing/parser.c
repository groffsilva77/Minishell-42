/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/15 18:52:46 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_or_get_command(t_command *atl_cmd)
{
	if (!atl_cmd)
		atl_cmd = create_command();
	printf("maçã");
	return (atl_cmd);
}

t_command	*handle_pipe(t_command *commands, t_command **atl_cmd)
{
	add_command(&commands, *atl_cmd);
	*atl_cmd = NULL;
	return (commands);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;
	char	quote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i];
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
	return (result);
}

int	handle_arg(t_command **atl_cmd, t_token *tokens, t_shell *shell)
{
	char	**temp;
	char	*expanded_value;
	char	*clean_value;

	if (!*atl_cmd)
		*atl_cmd = create_command();
	if (!*atl_cmd)
		return (-1);
	if (tokens->in_single_quotes)
		expanded_value = ft_strdup(tokens->value);
	else
		expanded_value = expand_tokens(shell, tokens->value, 1);
	if (!expanded_value)
		return (-1);
	clean_value = remove_quotes(expanded_value);
	free(expanded_value);
	if (!clean_value)
		return (-1);
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			clean_value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free(clean_value);
		return (-1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->argument_count++;
	free(clean_value);
	return (0);
}

t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*commands;
	t_command	*atl_cmd;

	commands = NULL;
	atl_cmd = NULL;
	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", 1) == 0)
			commands = handle_pipe(commands, &atl_cmd);
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!tokens->next)
				return (commands);
			if (!atl_cmd)
				atl_cmd = create_command();
			parse_redirections(atl_cmd, &tokens);
		}
		else if (handle_arg(&atl_cmd, tokens, shell) == -1)
			return (NULL);
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
