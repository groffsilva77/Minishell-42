/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:02:33 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 18:07:22 by ytavares         ###   ########.fr       */
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
			shell->env_copy[i] = ft_strjoin(name, "=", value_ex);
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
	new_env = realloc_array(shell->env_copy, sizeof(char *) * (i + 2));
	if (!new_env)
	{
		shell->exit_status = 1;
		return (1);
	}
	new_env[i] = ft_strjoin(name, "=", value_ex);
	new_env[i + 1] = NULL;
	shell->env_copy = new_env;
	free(name);
	free(value_ex);
	shell->exit_status = 0;
	return (0);
}

int	the_export(char **args, t_shell *shell)
{
	char	*eq_position;
	char	*name;
	char	*var_value;
	char	*value_ex;

	if (!args[1])
		return (the_env(shell));
	eq_position = ft_strchr(args[1], '=');
	if (!eq_position)
	{
		shell->exit_status = 1;
		return (1);
	}
	name = ft_strndup(args[1], eq_position - args[1]);
	var_value = ft_strdup(eq_position + 1);
	value_ex = expand_tokens(var_value);
	free(var_value);
	if (update_existing_var(name, value_ex, shell) == 0)
		return (0);
	return (add_new_var(name, value_ex, shell));
}
/*

Início
|
v
Verifica se args[1] existe?
|
+---> Não ---> Chama the_env(shell) e retorna
|
v
Sim
|
v
Procura o caractere '=' em args[1]
|
+---> Não encontrado ---> Define exit_status = 1 e retorna 1
|
v
Encontrado
|
v
Extrai o nome da variável (var_name) e o valor (var_value)
|
v
Expande o valor da variável (var_value_expanded)
|
v
Libera var_value (não é mais necessário)
|
v
Chama update_existing_var(var_name, var_value_expanded, shell)
|
+---> Variável existe? ---> Sim ---> Atualiza a variável existente
|        |                        |
|        |                        v
|        |                      Libera var_name e var_value_expanded
|        |                        |
|        |                        v
|        |                      Define exit_status = 0 e retorna 0
|        |
|        v
|       Não
|
v
Chama add_new_var(var_name, var_value_expanded, shell)
|
+---> Alocação de memória falhou? ---> Sim ---> Define exit_status = 1 e retorna 1
|        |
|        v
|       Não
|        |
|        v
|      Adiciona a nova variável ao array
|        |
|        v
|      Libera var_name e var_value_expanded
|        |
|        v
|      Define exit_status = 0 e retorna 0
|
v
Fim

*/