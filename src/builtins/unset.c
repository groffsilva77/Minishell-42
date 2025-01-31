/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:34:26 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 18:15:52 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//unset: Remover variáveis do ambiente

//execução: unset VARIAVEL (variavel que vc quer remover)

#include "minishell.h"

static int	find_and_remove_var(char **env_copy, char *var_name)
{
	int					i;
	int					j;
	size_t				len_var;

	i = 0;
	len_var = ft_strlen(var_name);
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], var_name, len_var) == 0
			&& (env_copy[i][len_var] == '=' || env_copy[i][len__var] == '\0'))
		{
			free(env_copy[i]);
			j = i;
			while (env_copy[j + 1])
			{
				env_copy[j] = env_copy[j + 1];
				j++;
			}
			env_copy[j] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	resize_env_array(t_shell *shell)
{
	char	**new_env;

	new_env = ft_realloc_array(shell->env_copy, sizeof(char *));
	if (!new_env)
	{
		shell->exit_status = 1;
		return (1);
	}
	shell->env_copy = new_env;
	shell->exit_status = 0;
	return (0);
}

int	the_unset(char **args, t_shell *shell)
{
	if (!args[1])
	{
		shell->exit_status = 0;
		return (0);
	}
	if (find_and_remove_var(shell->env_copy, args[1]))
		return (resize_env_array(shell));
	shell->exit_status = 0;
	return (0);
}

/*

Verifica se args[1] existe.
Não: Retorna 0.
Sim: Continua.

Tenta encontrar e remover a variável com find_and_remove_var.

Encontrada:
Remove a variável.
Reorganiza o array.
Chama resize_env_array para realocar o array.
Retorna 0 (sucesso).

Não encontrada:
Retorna 0.

Se a realocação falhar:
Define exit_status = 1.
Retorna 1.

Se a realocação for bem-sucedida:
Define exit_status = 0.
Retorna 0.

*/