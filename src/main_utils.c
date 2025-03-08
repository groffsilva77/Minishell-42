/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:45 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/08 18:36:19 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_command	*process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = tokenize(shell, input);
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

static void	handle_input(t_shell *shell, char *input)
{
	t_command	*commands;
	//int			result;

	//result = 0;
	if (is_empty_input(input))
	{
		free(input);
		return ;
	}
	commands = process_input(input, shell);
	if (!commands)
	{
		free(input);
		return ;
	}
	execute_single_command(commands, shell);
	free_commands(commands, shell);
	free(input);
	shell->expand[0] = '\0';
	/* if (result == -1)
	{
		free_shell(shell);
		exit(shell->exit_status);
	} */
}

void	shell_loop(t_shell *shell)
{
	char	*input;
	int		store_exit;

	printf("shell_loop: starting\n");
	while (1)
	{
		input = get_user_input();
		if (!input)
		{
			write(1, "exit\n", 5);
			store_exit = shell->exit_status;
			printf("shell_loop: calling free_shell before exit\n");
			free_shell(shell);
			printf("shell_loop: exiting with status=%d\n", store_exit);
			exit(store_exit);
		}
		printf("shell_loop: input=%s\n", input);
		handle_input(shell, input);
	}
}
