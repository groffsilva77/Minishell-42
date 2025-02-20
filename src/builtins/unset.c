/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:34:26 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/20 15:55:17 by ytavares         ###   ########.fr       */
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
	printf("Procurando pela variável: '%s'\n", var_name);
	while (env_copy[i])
	{
		printf("Comparando: '%s' com '%s' (tamanho: %zu)\n", env_copy[i], var_name, len_var);
		if (ft_strncmp(env_copy[i], var_name, len_var) == 0
			&& (env_copy[i][len_var] == '=' || env_copy[i][len_var] == '\0'))
		{
			printf("Removendo variável: '%s'\n", env_copy[i]);
			//free(env_copy[i]);
			j = i;
			while (env_copy[j + 1])
			{
				env_copy[j] = env_copy[j + 1];
				printf("Movendo variável: '%s' para posição %d\n", env_copy[j], j);
				j++;
			}
			env_copy[j] = NULL;
			printf("Variável '%s' removida com sucesso.\n", var_name);
			return (1);
		}
		i++;
	}
	printf("Variável '%s' não encontrada no ambiente.\n", var_name);
	return (0);
}

static int	resize_env_array(t_shell *shell)
{
	char	**new_env;
	int		size;

	size = 0;
	while (shell->env_copy[size])
		size++;
	printf("Redimensionando o array de ambiente para tamanho %d...\n", size);
	new_env = ft_realloc_array(shell->env_copy, size, NULL, shell);
	if (!new_env)
	{
		printf("Falha ao redimensionar o array de ambiente.\n");
		shell->exit_status = 1;
		return (1);
	}
	shell->env_copy = new_env;
	shell->exit_status = 0;
	printf("Array de ambiente redimensionado com sucesso.\n");
	return (0);
}

int	the_unset(char **args, t_shell *shell)
{
	int i;

	if (!args[1])
	{
		shell->exit_status = 0;
		return (0);
	}
	printf("\nVariáveis antes do unset:\n");
	i = 0;
	while (shell->env_copy[i])
		printf("[%d]: %s\n", i++, shell->env_copy[i]);
	printf("Chamando unset para a variável: '%s'\n", args[1]);
	if (find_and_remove_var(shell->env_copy, args[1]))
	{
		printf("\nVariáveis após remoção:\n");
        i = 0;
        while (shell->env_copy[i])
            printf("[%d]: %s\n", i++, shell->env_copy[i]);
		return (resize_env_array(shell));
	}
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