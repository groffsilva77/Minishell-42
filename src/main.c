/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/28 18:50:50 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	process_tokens(t_token *tokens)
{
	t_token	*current;
	char	*expanded_value;

	current = tokens;
	while (current)
	{
		expanded_value = expand_tokens(current->value);
		printf("Expanded token: '%s'\n", expanded_value);
		free(expanded_value);
		current = current->next;
	}
}

char	*get_user_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}

void	shell_loop(t_shell *shell)
{
	char		*input;
	t_token		*tokens;
	t_command	*commands;

	while (1)
	{
		input = get_user_input();
		if (!input)
			break ;
		tokens = tokenize(input);
		if (!validate_syntax(tokens))
		{
			free_tokens(tokens);
			free(input);
			continue ;
		}
		commands = parse_tokens(tokens);
		process_tokens(tokens);
		execute_commands(commands, shell);
		free_tokens(tokens);
		free_commands(commands, shell);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.memory = NULL;
	shell.env_copy = envp;
	shell.exit_status = 0;
	shell_loop(&shell);
	ft_free_all(&shell);
	return (0);
}
