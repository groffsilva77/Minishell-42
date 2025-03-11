/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:45 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/11 17:12:42 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*process_input(char *input, t_shell *shell)
{
	t_token		*tokens;

	tokens = tokenize(shell, input);
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens, shell))
	{
		shell->exit_status = 2;
		return (NULL);
	}
	shell->commands = parse_tokens(tokens, shell);
	execute_single_command(shell->commands, shell);
	free_tokens(tokens);
	return (shell->commands);
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

static void	handle_input(t_shell *shell, char *input)
{
	t_command	*commands;

	if (is_empty_input(input))
	{
		free(input);
		return ;
	}
	commands = process_input(input, shell);
	if (commands)
		free_commands(commands, shell);
	shell->expand[0] = '\0';
}

void	shell_loop(t_shell *shell)
{
	char	*input;
	int		store_exit;

	while (1)
	{
		input = get_user_input();
		if (!input)
		{
			write(1, "exit\n", 5);
			store_exit = shell->exit_status;
			free(shell);
			exit(store_exit);
			break ;
		}
		handle_input(shell, input);
	}
}
