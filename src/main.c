/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/22 17:18:44 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

void	shell_loop(void)
{
	t_token	*tokens;
	char	*input;

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
		process_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
}

int	main(void)
{
	shell_loop();
	return (0);
}

// int	main(void)
// {
// 	t_token	*tokens;
// 	t_token	*current;
// 	char	*input;
// 	char	*expanded_value;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 			add_history(input);
// 		tokens = tokenize(input);
// 		if (!validate_syntax(tokens))
// 		{
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}
// 		current = tokens;
// 		while (current)
// 		{
// 			expanded_value = expand_tokens(current->value);
// 			printf("Token expandido: '%s'\n", expanded_value);
// 			free(expanded_value);
// 			current = current->next;
// 		}
// 		free_tokens(tokens);
// 		free(input);
// 	}
// 	return (0);
// }
