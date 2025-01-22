/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/22 13:49:19 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: '%s'\n", tokens->value);
		tokens = tokens->next;
	}
}

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

int	main(void)
{
	t_token	*tokens;
	t_token	*current;
	char	*input;
	char	*expanded_value;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		current = tokens;
		while (current)
		{
			expanded_value = expand_tokens(current->value);
			printf("Token expandido: '%s'\n", expanded_value);
			free(expanded_value);
			current = current->next;
		}
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
