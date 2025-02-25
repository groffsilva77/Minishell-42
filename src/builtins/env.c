/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:23:11 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/25 14:04:13 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	the_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env_copy || !shell->env_copy[0])
	{
		shell->exit_status = 1;
		return (1);
	}
	while (shell->env_copy[i])
	{
		printf("%s\n", shell->env_copy[i]);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}
