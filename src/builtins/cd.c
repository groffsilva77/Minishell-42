/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:23:11 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/02 16:23:59 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cd: entra dentro de diretórios

/*char args: contém os argumetos passados pelo usuário.
t_shell: um ponteiro para a struct de dados*/

#include "minishell.h"

static void	update_env_var(t_shell *shell, const char *name, const char *value)
{
	int		i;
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_var;
			return ;
		}
		i++;
	}
	shell->env_copy = realloc_array(shell->env_copy, sizeof(char *) * (i + 2));
	shell->env_copy[i] = new_var;
	shell->env_copy[i + 1] = NULL;
}

static int	change_directory(char *new_dir, t_shell *shell, char *atl_dir)
{
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		shell->exit_status = 1;
		free(new_dir);
		return (1);
	}
	update_env_var(shell, "OLDPWD", atl_dir);
	update_env_var(shell, "PWD", new_dir);
	free(new_dir);
	shell->exit_status = 0;
	return (0);
}

static int	handle_no_args(t_shell *shell, char **new_path_dir)
{
	char	*store_home;

	store_home = get_env_value("HOME");
	if (!store_home || !*store_home)
	{
		printf("cd: HOME is not defined\n");
		shell->exit_status = 1;
		return (1);
	}
	*new_dir = store_home;
	return (0);
}

int	the_cd(char **args, t_shell *shell)
{
	char	*new_p_dir;
	char	store_atl_dir[1024];

	if (getcwd(store_atl_dir, sizeof(store_atl_dir)) == NULL)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (!args[1])
	{
		if (handle_no_args(shell, &new_path_dir) != 0)
			return (1);
	}
	else
	{
		new_path_dir = expand_tokens(args[1]);
		if (!new_path_dir)
		{
			shell->exit_status = 1;
			return (1);
		}
	}
	return (change_directory(new_path_dir, shell, store_atl_dir));
}

/*
	new_path_dir; //armazenará o caminho do diretório para aonde o shell vai mudar
	store_atl_dir[1024]; //buffer para armazenar o diretório atual(antes de mudar)
	*store_home; //armazena o valor da variável de ambiente HOME, caso o usuario não passe um caminho no comando cd.


Primeiro, ela armazena o diretório atual em store_atl_dir:

Usa getcwd para obter o caminho atual e o diretório atual
Se falhar, retorna erro

Se não houver argumentos (args[1] é NULL), chama handle_no_args:

Obtém o valor da variável HOME usando get_env_value
Se HOME não estiver definida, exibe erro
Define o novo caminho como o valor de HOME

Se houver argumento:

Expande possíveis tokens no argumento usando expand_tokens
O resultado é armazenado em new_path_dir

Executa a mudança de diretório com change_directory:

Usa chdir para mudar para o novo diretório
Se falhar, exibe erro com perror
Define store_atl_dir como o diretório anterior
Define new_path_dir como o novo diretório

{ ao mudar de diretório, é necessário atualizar as variáveis de ambiente PWD (diretório atual) e OLDPWD (diretório anterior)}
Libera a memória alocada para new_path_dir

Se a mudança for bem-sucedida:

Atualiza as variáveis PWD e OLDPWD com update_pwd
Define exit_status como 0
Retorna sucesso
*/