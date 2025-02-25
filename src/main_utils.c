/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:45 by ggroff-d          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/25 15:15:47 by ytavares         ###   ########.fr       */
=======
/*   Updated: 2025/02/19 19:04:13 by ggroff-d         ###   ########.fr       */
>>>>>>> 61e53790d7d686fd655c7b05c5e64901fb0963bc
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	expand_tokens(shell, input, 1);
	execute_single_command(commands, shell);
	free_commands(commands, shell);
	free(input);
}

void	shell_loop(t_shell *shell)
{
<<<<<<< HEAD
	char	*input;
	int		store_exit;
=======
	char			*input;
	// char			*expanded;
	t_command		*commands;
>>>>>>> 61e53790d7d686fd655c7b05c5e64901fb0963bc

	while (1)
	{
		input = get_user_input();
		if (!input)
		{
			write(1, "exit", 5);
			store_exit = shell->exit_status;
			ft_free_all(shell);
			exit(store_exit);
		}
<<<<<<< HEAD
		handle_input(shell, input);
=======
		commands = process_input(input, shell);
		if (!commands)
		{
			free(input);
			continue ;
		}
		// expanded = expand_tokens(input, 1);
		// free(expanded);
		execute_single_command(commands, shell);
		free_commands(commands, shell);
		free(input);
>>>>>>> 61e53790d7d686fd655c7b05c5e64901fb0963bc
	}
}
