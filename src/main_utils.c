/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:45 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/18 14:27:20 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	commands = parse_tokens(tokens, shell);
	free_tokens(tokens);
	return (commands);
}

char	*get_user_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}

int	is_empty_input(const char *input)
{
	while (*input)
	{
		if (!is_whitespace(*input))
			return (0);
		input++;
	}
	return (1);
}

void	shell_loop(t_shell *shell)
{
	char			*input;
	char			*expanded;
	t_command		*commands;

	while (1)
	{
		input = get_user_input();
		if (!input || is_empty_input(input))
		{
			free(input);
			continue ;
		}
		commands = process_input(input, shell);
		if (!commands)
		{
			free(input);
			continue ;
		}
		expanded = expand_tokens(input, 1);
		free(expanded);
		execute_single_command(commands, shell);
		free_commands(commands, shell);
		free(input);
	}
}
