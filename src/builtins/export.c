/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:02:33 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/16 14:59:01 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
export: define ou atualiza variáveis de ambiente

Listar variáveis de ambiente (quando executado sem argumentos).
Criar ou atualizar variáveis de ambiente.
Fazer com que uma variável local seja reconhecida como variável de ambiente.

execusão: export VAR=42 (exemplo)

env_copy: (array de strings com as variáveis de ambiente).
*/

#include "minishell.h"

static int	update_existing_var(char *name, char *value_ex, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			free(shell->env_copy[i]);
			shell->env_copy[i] = fts_strjoin(shell, "=", value_ex);
			free(name);
			free(value_ex);
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
	int		i;

	i = 0;
	while (shell->env_copy[i])
		i++;
	new_env = ft_realloc_array(shell->env_copy, sizeof(char *) * (i + 2),
			value_ex, shell);
	if (!new_env)
	{
		shell->exit_status = 1;
		return (1);
	}
	new_env[i] = fts_strjoin(shell, "=", value_ex);
	new_env[i + 1] = NULL;
	shell->env_copy = new_env;
	free(name);
	free(value_ex);
	shell->exit_status = 0;
	return (0);
}

int	the_export(char **args, t_shell *shell)
{
	const char	*eq_position;
	char		*name;
	char		*var_value;
	char		*value_ex;

	if (!args[1])
		return (the_env(shell));
	eq_position = ft_strchr(args[1], '=');
	if (!eq_position)
	{
		shell->exit_status = 1;
		return (1);
	}
	name = fts_strdup(shell, eq_position);
	var_value = fts_strdup(shell, eq_position);
	value_ex = expand_tokens(var_value, 1);
	free(var_value);
	if (update_existing_var(name, value_ex, shell) == 0)
		return (0);
	return (add_new_var(name, value_ex, shell));
}
