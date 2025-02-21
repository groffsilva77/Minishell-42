/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:45 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/21 19:25:18 by ytavares         ###   ########.fr       */
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

void	shell_loop(t_shell *shell)
{
	char			*input;
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
		expand_tokens(shell, input, 1);
		free(shell->expand);
		execute_single_command(commands, shell);
		free_commands(commands, shell);
		free(input);
	}
}

t_shell *init_shell(char **env)
{
    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    shell->expand = malloc(4096);  // Tamanho fixo para expansões
    shell->sbstr = malloc(4096);   // Tamanho fixo para substrings
    if (!shell->expand || !shell->sbstr)
    {
        free(shell->expand);
        free(shell->sbstr);
        free(shell);
        return (NULL);
    }
    shell->memory = NULL;
    shell->env_copy = duplicate_env(env);
	if (!shell->env_copy)
    {
        free(shell->expand);
        free(shell->sbstr);
        free(shell);
        return (NULL);
    }
    shell->exit_status = 0;
    return (shell);
}

void free_shell(t_shell *shell)
{
	int i = 0;
    if (shell)
    {
        free(shell->expand);
        free(shell->sbstr);
		if (shell->env_copy)
		{
			while (shell->env_copy[i])
				free(shell->env_copy[i++]);
			free(shell->env_copy);
		}
        free(shell->memory);
        free(shell);
    }
}


char **duplicate_env(char **env)
{
    int     i;
    char    **copy;

    if (!env)
        return (NULL);
    i = 0;
    while (env[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (env[i])
    {
        copy[i] = ft_strdup(env[i]);
        if (!copy[i])
        {
            while (i > 0)
                free(copy[--i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}
