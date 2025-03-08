/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/08 20:21:04 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_or_get_command(t_command *atl_cmd)
{
	if (!atl_cmd)
		atl_cmd = create_command();
	return (atl_cmd);
}

t_command	*handle_pipe(t_command *commands, t_command **atl_cmd)
{
	add_command(&commands, *atl_cmd);
	*atl_cmd = NULL;
	return (commands);
}

static char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	char	outer_quote;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	outer_quote = 0;
	if ((str[0] == '"' || str[0] == '\'') &&
		str[0] == str[ft_strlen(str) - 1])
		outer_quote = str[0];
	while (str[i])
	{
		if ((i == 0 || i == ft_strlen(str) - 1) && str[i] == outer_quote)
			;
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

	printf("handle_arg: token=%s, in_squotes=%d, in_dquotes=%d\n", 
           tokens->value, tokens->in_single_quotes, tokens->in_double_quotes);
	if (tokens->in_single_quotes)
		expanded_value = ft_strdup(tokens->value);
	else
		expanded_value = expand_tokens(shell, tokens->value, 1);
	printf("handle_arg: expanded_value=%s\n", expanded_value);
	if (!expanded_value)
		return (-1);
	clean_value = remove_quotes(expanded_value);
	printf("handle_arg: clean_value=%s\n", clean_value);
	free(expanded_value);
	*atl_cmd = create_or_get_command(*atl_cmd);
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			clean_value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free(clean_value);
		return (free((*atl_cmd)->args), (*atl_cmd)->args = NULL, -1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->args[(*atl_cmd)->argument_count] = clean_value;
	(*atl_cmd)->argument_count++;
	return ((*atl_cmd)->args[(*atl_cmd)->argument_count] = NULL, 0);
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
