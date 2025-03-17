/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:34:26 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/17 19:49:40 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			&& (env_copy[i][len_var] == '=' || env_copy[i][len_var] == '\0'))
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
static int resize_env_array(t_shell *shell)
{
    char **new_env;
    int size = 0;
    int i;

    while (shell->env_copy[size])
        size++;
    new_env = malloc(sizeof(char *) * (size + 1));
    if (!new_env)
    {
        shell->exit_status = 1;
        return (1);
    }
    i = 0;
    while (i < size && shell->env_copy[i])
    {
        new_env[i] = shell->env_copy[i];
        i++;
    }
    new_env[i] = NULL;
    free(shell->env_copy);
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
