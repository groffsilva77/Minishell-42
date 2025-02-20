/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:02:33 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/20 13:32:41 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing_var(char *name, char *value_ex, t_shell *shell)
{
	int		i;
	char	*new_value;
	char	*temp;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (1);
			new_value = ft_strjoin(temp, value_ex);
			free(temp);
			if (!new_value)
				return (1);
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_value;
			shell->exit_status = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	add_new_var(char *name, char *value_ex, t_shell *shell)
{
	char	**new_env;
	char	*temp;
	char	*new_value;
	int		i;

	i = 0;
	while (shell->env_copy[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (shell->env_copy[i])
	{
		new_env[i] = shell->env_copy[i];
		i++;
	}
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (free(new_env), 1);
	new_value = ft_strjoin(temp, value_ex);
	free(temp);
	if (!new_value)
		return (free(new_env), 1);
	new_env[i] = new_value;
	new_env[i + 1] = NULL;
	shell->env_copy = new_env;
	shell->exit_status = 0;
	return (0);
}

int	the_export(char **args, t_shell *shell)
{
	const char	*eq_position;
	char		*name;
	char		*value_ex;
	size_t		name_len;

	if (!args[1])
		return (the_env(shell));
	eq_position = ft_strchr(args[1], '=');
	if (!eq_position)
		return (0);
	name_len = eq_position -args[1];
	printf("Tamanho do nome: %zu\n", name_len);
	printf("Argumento recebido: '%s'\n", args[1]);
	name = malloc(name_len + 1);
	if (!name)
		return (1);
	memcpy(name, args[1], name_len);
	name[name_len] = '\0';
	printf ("nome extraido: %s\n", name);
	value_ex = expand_tokens(shell, eq_position + 1, 1);
	if (!value_ex)
	{
		printf("Erro: Expansão de tokens falhou!\n");
		return (free(name), 1);
	}
	if (update_existing_var(name, value_ex, shell) != 0)
	{
		if (add_new_var(name, value_ex, shell) != 0)
			return (free(name), free(value_ex), 1);
	}
	free(name);
	int i = 0;
	while(shell->env_copy[i])
	{
		printf("env[%d]: %s\n", i, shell->env_copy[i]);
		i++;
	}
	return (0);
}
